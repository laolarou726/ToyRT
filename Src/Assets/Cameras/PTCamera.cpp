//
// Created by luoli on 2022/10/19.
//

#include "PTCamera.h"
#include "../Ray.h"
#include "../../Models/Rgb.h"
#include <iostream>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>
#include "fmt/format.h"
#include "../../Utils/GammaUtils.h"

PTCamera::PTCamera(double portSizeWidth, double portSizeHeight, double focus, const Vector3 &origin,
                   const Vector3 &direction) {
    this->portSizeWidth = portSizeWidth;
    this->portSizeHeight = portSizeHeight;
    this->focus = focus;
    this->origin = origin;

    Vector3 d = direction;
    d.normalize();
    this->direction = d;

    const int maxNumThreads = omp_get_max_threads();
    std::string threadMessage = fmt::format("Maximum number of threads for this machine: {}", maxNumThreads);
    std::cout << threadMessage << std::endl;

    omp_set_num_threads(maxNumThreads);
}

void PTCamera::render(int resWidth, int resHeight, const Scene &scene) {
    PPM myImage = easyppm_create(resWidth, resHeight, IMAGETYPE_PPM);
    GammaUtils gamma(this->gammaCorrectionFactor);

    // Clear all image pixels to RGB color white.
    easyppm_clear(&myImage, easyppm_rgb(0, 0, 0));

    Vector3 vecX = Vector3::unitZ().cross(direction);
    vecX.normalize();

    std::vector<std::vector<int>> iterCountArr(resWidth, std::vector<int>(resHeight, 0));
    std::vector<std::vector<Vector3*>> pixelColorBuffer(resWidth, std::vector<Vector3*>(resHeight, nullptr));

    Vector3 vecY = Vector3::unitZ();
    Vector3 B = (focus * direction) +
                (0.5 * portSizeWidth * vecX) +
                (0.5 * portSizeHeight * vecY);
    std::mutex mutex;
    oneapi::tbb::task_arena arena;
    size_t currentIterCount = 0;

    arena.execute([&]{
        oneapi::tbb::parallel_for(tbb::blocked_range<size_t>(0, iterCount),
                [&](tbb::blocked_range<size_t> &iterRange) {
            size_t totalBatchIter = 0;

            for (size_t currentIter = iterRange.begin(); currentIter != iterRange.end(); currentIter++){

                oneapi::tbb::parallel_for(tbb::blocked_range<size_t>(0, samplePerIter),
                                          [&](tbb::blocked_range<size_t> &sampleIterRange){
                    for (size_t currentSample = sampleIterRange.begin(); currentSample != sampleIterRange.end(); currentSample++){
                        int x = Random::nextInt(resWidth - 1);
                        int y = Random::nextInt(resHeight - 1);

                        Vector3 emitResultColor;

                        for(size_t antiAlCount = 0; antiAlCount < this->antiAliasingSampleCount; antiAlCount++){
                            double biasedX = x + Random::next(-1, 1);
                            double biasedY = y + Random::next(-1, 1);
                            double portX = (double) biasedX / resWidth * portSizeWidth;
                            double portY = (double) biasedY / resHeight * portSizeHeight;

                            Vector3 P = B - portX * vecX - portY * vecY;
                            Ray ray = Ray(origin, P);
                            Vector3 tempEmitResultColor = ray.emit(scene);

                            emitResultColor = emitResultColor + tempEmitResultColor;
                        }

                        emitResultColor = emitResultColor / this->antiAliasingSampleCount;

                        // Gamma Correction
                        emitResultColor.x = pow(emitResultColor.x, 1.0 / this->gammaCorrectionFactor);
                        emitResultColor.y = pow(emitResultColor.y, 1.0 / this->gammaCorrectionFactor);
                        emitResultColor.z = pow(emitResultColor.z, 1.0 / this->gammaCorrectionFactor);

                        mutex.lock();
                        {
                            if (pixelColorBuffer[x][y] == nullptr)
                                pixelColorBuffer[x][y] = new Vector3();

                            emitResultColor =
                                    (iterCountArr[x][y] * *pixelColorBuffer[x][y] + emitResultColor) /
                                    (iterCountArr[x][y] + 1);
                        }
                        mutex.unlock();

                        Rgb color = Rgb(emitResultColor.x, emitResultColor.y, emitResultColor.z);

                        char r = (char) (color.getR() * 255);
                        char g = (char) (color.getG() * 255);
                        char b = (char) (color.getB() * 255);

                        mutex.lock();
                        {
                            pixelColorBuffer[x][y] = new Vector3(emitResultColor.x,
                                                                 emitResultColor.y,
                                                                 emitResultColor.z);

                            easyppm_set(&myImage,
                                        x, y,
                                        easyppm_rgb(r, g, b));

                            iterCountArr[x][y]++;
                        }
                        mutex.unlock();
                    }
                });

                totalBatchIter++;
            }

            currentIterCount += totalBatchIter;
            double progress = (double) currentIterCount / iterCount * 100;
            reportProgress(progress, 5);
        });
    });

    this->image = myImage;
}

int PTCamera::getIterationCount() const {
    return iterCount;
}

void PTCamera::setIterationCount(int count) {
    this->iterCount = count;
}

int PTCamera::getSamplePerIteration() const {
    return samplePerIter;
}

void PTCamera::setSamplePerIteration(int count) {
    this->samplePerIter = count;
}

int PTCamera::getAntiAliasingSampleCount() const {
    return this->antiAliasingSampleCount;
}

void PTCamera::setAntiAliasingSampleCount(int count) {
    this->antiAliasingSampleCount = count;
}

double PTCamera::getGammaCorrectionFactor() const {
    return this->gammaCorrectionFactor;
}

void PTCamera::setGammaCorrectionFactor(double factor) {
    this->gammaCorrectionFactor = factor;
}
