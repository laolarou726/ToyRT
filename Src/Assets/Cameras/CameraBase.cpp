//
// Created by luoli on 2022/10/19.
//

#include "CameraBase.h"
#include "fmt/format.h"
#include <fmt/chrono.h>

void CameraBase::render(int resWidth, int resHeight, const Scene &scene) {
    throw std::invalid_argument("not implemented");
}

CameraBase::~CameraBase() {
    easyppm_destroy(&image);
}

void CameraBase::reportProgress(double progress, int reportStep) {
    int ceilProgress = ceil(progress);

    if(ceilProgress == 0){
        std::cout << "[  0%] RENDER PROGRESS" << std::endl;
        return;
    }

    if(ceilProgress == lastReportValue) return;

    if(ceilProgress % reportStep == 0){
        const auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string message = fmt::format("[{:%H:%M:%S}] [{:>4}%] RENDER PROGRESS", fmt::localtime(t), ceilProgress);
        std::cout << message << std::endl;
        lastReportValue = ceilProgress;
        return;
    }
}
