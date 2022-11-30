//
// Created by luoli on 2022/10/19.
//

#ifndef COMPUTERGRAPHICS_PTCAMERA_H
#define COMPUTERGRAPHICS_PTCAMERA_H


#include "CameraBase.h"

class PTCamera : public CameraBase{
private:
    int iterCount = 100000;
    int samplePerIter = 128;
public:
    PTCamera(double portSizeWidth, double portSizeHeight, double focus, const Tuple &origin, const Tuple &direction);
    void render(int resWidth, int resHeight, const Scene &scene) override;
    [[nodiscard]] int getIterationCount() const;
    void setIterationCount(int count);
    [[nodiscard]] int getSamplePerIteration() const;
    void setSamplePerIteration(int count);
};


#endif //COMPUTERGRAPHICS_PTCAMERA_H
