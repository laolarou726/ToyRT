//
// Created by luoli on 2022/10/12.
//

#include "Reflection.h"
#include "cmath"
#include "../Objects/Sphere.h"

Vector3 Reflection::getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) {
    Vector3 reflected = inRay - meshNormal * (inRay.dot(meshNormal)) * 2.0f;
    Vector3 outRay = reflected + roughness * Sphere::randomInUnitSphere();

    return outRay;
}

Reflection::Reflection(const Vector3 &reflectance, double roughness) {
    this->reflectance = reflectance;
    this->roughness = roughness < 1 ? roughness : 1;
}
