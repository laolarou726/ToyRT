//
// Created by luoli on 2022/9/25.
//

#include "MaterialBase.h"
#include <cmath>

Tuple MaterialBase::getEmission() const {
    return emission;
}

Tuple MaterialBase::getReflectance() const {
    return reflectance;
}

tuple<char, char, char> MaterialBase::getReflectanceColor() const {
    return std::make_tuple(
            (char) round(reflectance.x * 255),
            (char) round(reflectance.y * 255),
            (char) round(reflectance.z * 255));
}

Tuple MaterialBase::getOutRayDirection(const Tuple &InRayDirection, const Tuple &MeshNormal) {
    throw std::invalid_argument("not implemented");
}
