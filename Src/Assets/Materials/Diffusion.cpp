//
// Created by luoli on 2022/9/25.
//

#include "Diffusion.h"

Diffusion::Diffusion(const Tuple &reflectance) {
    this->reflectance = reflectance;
}

Tuple Diffusion::getOutRayDirection(const Tuple &inRay, const Tuple &meshNormal) {
    while (true){
        Tuple randomVec = Tuple::RAND_NORM();
        if(randomVec.dot(meshNormal) > 0) return randomVec;
    }
}
