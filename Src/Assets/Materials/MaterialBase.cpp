//
// Created by luoli on 2022/9/25.
//

#include "MaterialBase.h"
#include <cmath>

Vector3 MaterialBase::getEmission() const {
    return emission;
}

Vector3 MaterialBase::getReflectance() const {
    return reflectance;
}

tuple<char, char, char> MaterialBase::getReflectanceColor() const {
    return std::make_tuple(
            (char) round(reflectance.x * 255),
            (char) round(reflectance.y * 255),
            (char) round(reflectance.z * 255));
}

Vector3 MaterialBase::getOutRayDirection(const Vector3 &InRayDirection, const Vector3 &MeshNormal) {
    throw std::invalid_argument("not implemented");
}
