//
// Created by luoli on 2022/9/25.
//

#include "Diffusion.h"

Diffusion::Diffusion(const Vector3 &reflectance) {
    this->reflectance = reflectance;
}

Vector3 Diffusion::getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) {
    while (true){
        Vector3 randomVec = Vector3::RAND_NORM();
        if(randomVec.dot(meshNormal) > 0) return randomVec;
    }
}
