//
// Created by luoli on 2022/10/19.
//

#include "CameraBase.h"

void CameraBase::render(int resWidth, int resHeight, const Scene &scene) {
    throw std::invalid_argument("not implemented");
}

CameraBase::~CameraBase() {
    easyppm_destroy(&image);
}

void CameraBase::reportProgress(double progress, int reportStep) {
    int ceilProgress = ceil(progress);

    if(ceilProgress == 0){
        std::cout << "[ 0% ] RENDER PROGRESS" << std::endl;
        return;
    }

    if(ceilProgress == lastReportValue) return;

    if(ceilProgress % reportStep == 0){
        std::cout << "[ " << ceilProgress << "% ] RENDER PROGRESS" << std::endl;
        lastReportValue = ceilProgress;
        return;
    }
}
