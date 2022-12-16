//
// Created by luoli on 2022/12/13.
//

#ifndef TOYRT_SINGLETHREADPTCAMERA_H
#define TOYRT_SINGLETHREADPTCAMERA_H


#include "../Scene.h"
#include "CameraBase.h"

class SingleThreadPTCamera : public CameraBase {
private:
    int iterCount = 100000;
    int samplePerIter = 128;
    int antiAliasingSampleCount = 5;
    double gammaCorrectionFactor = 1;
public:
    SingleThreadPTCamera(double portSizeWidth, double portSizeHeight, double focus, const Vector3 &origin, const Vector3 &direction);
    void render(int resWidth, int resHeight, const Scene &scene) override;
    [[nodiscard]] double getGammaCorrectionFactor() const;
    void setGammaCorrectionFactor(double factor);
    [[nodiscard]] int getAntiAliasingSampleCount() const;
    void setAntiAliasingSampleCount(int count);
    [[nodiscard]] int getIterationCount() const;
    void setIterationCount(int count);
    [[nodiscard]] int getSamplePerIteration() const;
    void setSamplePerIteration(int count);
};


#endif //TOYRT_SINGLETHREADPTCAMERA_H
