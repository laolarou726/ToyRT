//
// Created by luoli on 2022/10/19.
//

#include "PTCamera.h"
#include "../Ray.h"
#include "../../Rgb.h"
#include <iostream>
#include <oneapi/tbb/info.h>
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/task_arena.h>

PTCamera::PTCamera(double portSizeWidth, double portSizeHeight, double focus, const Tuple &origin,
                   const Tuple &direction) {
    this->portSizeWidth = portSizeWidth;
    this->portSizeHeight = portSizeHeight;
    this->focus = focus;
    this->origin = origin;

    Tuple d = direction;
    d.normalize();
    this->direction = d;

    const int maxNumThreads = omp_get_max_threads();
    std::cout << "Maximum number of threads for this machine: " << maxNumThreads << std::endl;

    omp_set_num_threads(maxNumThreads);
}

void PTCamera::render(int resWidth, int resHeight, const Scene &scene) {
    PPM myImage = easyppm_create(resWidth, resHeight, IMAGETYPE_PPM);

    // Clear all image pixels to RGB color white.
    easyppm_clear(&myImage, easyppm_rgb(0, 0, 0));

    Tuple vecX = Tuple::unitZ().cross(direction);
    vecX.normalize();

    std::vector<std::vector<int>> iterCountArr(resWidth, std::vector<int>(resHeight, 0));
    std::vector<std::vector<Tuple*>> pixelColorBuffer(resWidth, std::vector<Tuple*>(resHeight, nullptr));

    Tuple vecY = Tuple::unitZ();
    Tuple B = (focus * direction) +
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
                for (size_t currentSample = 0; currentSample < samplePerIter; currentSample++){
                    int x = Random::nextInt(resWidth - 1);
                    int y = Random::nextInt(resHeight - 1);
                    double portX = (double) x / resWidth * portSizeWidth;
                    double portY = (double) y / resHeight * portSizeHeight;

                    Tuple P = B - portX * vecX - portY * vecY;
                    Ray ray = Ray(origin, P);
                    Tuple emitResultColor = ray.emit(scene);

                    mutex.lock();
                    {
                        if (pixelColorBuffer[x][y] == nullptr)
                            pixelColorBuffer[x][y] = new Tuple();

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
                        pixelColorBuffer[x][y] = new Tuple(emitResultColor.x,
                                                           emitResultColor.y,
                                                           emitResultColor.z);

                        easyppm_set(&myImage,
                                    x, y,
                                    easyppm_rgb(r, g, b));

                        iterCountArr[x][y]++;
                    }
                    mutex.unlock();
                }

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
