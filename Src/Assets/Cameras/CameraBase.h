//
// Created by luoli on 2022/10/19.
//

#ifndef COMPUTERGRAPHICS_CAMERABASE_H
#define COMPUTERGRAPHICS_CAMERABASE_H

#include <omp.h>
#include "../../Models/Vector3.h"
#include "../Scene.h"
#include "../../Utils/easyppm.h"

class CameraBase {
private:
    int lastReportValue;
protected:
    double portSizeWidth;
    double portSizeHeight;
    double focus;
    Vector3 origin;
    Vector3 direction;
    PPM image;

    virtual void reportProgress(double progress, int reportStep);
public:
    virtual void render(int resWidth, int resHeight, const Scene &scene);
    virtual void saveTo(const std::string &path){
        easyppm_write(&image, path.c_str());
    }
    ~CameraBase();
};


#endif //COMPUTERGRAPHICS_CAMERABASE_H
