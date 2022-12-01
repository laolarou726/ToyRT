//
// Created by luoli on 2022/10/12.
//

#include "Reflection.h"
#include "cmath"

Vector3 Reflection::getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) {
    Vector3 outRay =
            inRay - 2 * inRay.dot(meshNormal)
            / pow(meshNormal.magnitude(), 2) *
            meshNormal;
    return outRay;
}

Reflection::Reflection(const Vector3 &reflectance) {
    this->reflectance = reflectance;
}
