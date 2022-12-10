//
// Created by luoli on 2022/9/25.
//

#include "Diffusion.h"
#include "../Objects/Sphere.h"

Diffusion::Diffusion(const Vector3 &reflectance) {
    this->reflectance = reflectance;
}

Vector3 Diffusion::getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) {
    return meshNormal + Sphere::randomInUnitSphere();
}
