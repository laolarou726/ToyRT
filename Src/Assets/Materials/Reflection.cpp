//
// Created by luoli on 2022/10/12.
//

#include "Reflection.h"
#include "cmath"

Tuple Reflection::getOutRayDirection(const Tuple &inRay, const Tuple &meshNormal) {
    Tuple outRay =
            inRay - 2 * inRay.dot(meshNormal)
            / pow(meshNormal.magnitude(), 2) *
            meshNormal;
    return outRay;
}

Reflection::Reflection(const Tuple &reflectance) {
    this->reflectance = reflectance;
}
