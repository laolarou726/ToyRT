//
// Created by luoli on 2022/10/20.
//

#include "Emission.h"

Emission::Emission(const Tuple &reflectance) {
    this->reflectance = reflectance;
}

Emission::Emission(const Tuple &reflectance, const Tuple &emission) {
    this->reflectance = reflectance;
    this->emission = emission;
}

Tuple Emission::getOutRayDirection(const Tuple &inRay, const Tuple &meshNormal) {
    while (true){
        Tuple randomVec = Tuple::RAND_NORM();
        if(randomVec.dot(meshNormal) > 0) return randomVec;
    }
}
