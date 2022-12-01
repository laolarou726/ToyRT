//
// Created by luoli on 2022/10/20.
//

#include "Emission.h"

Emission::Emission(const Vector3 &reflectance) {
    this->reflectance = reflectance;
}

Emission::Emission(const Vector3 &reflectance, const Vector3 &emission) {
    this->reflectance = reflectance;
    this->emission = emission;
}

Vector3 Emission::getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) {
    while (true){
        Vector3 randomVec = Vector3::RAND_NORM();
        if(randomVec.dot(meshNormal) > 0) return randomVec;
    }
}
