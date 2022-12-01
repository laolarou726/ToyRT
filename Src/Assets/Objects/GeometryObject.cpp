//
// Created by luoli on 2022/9/22.
//

#include "GeometryObject.h"

GeometryObject::GeometryObject(const Vector3 &position) {
    this->position = position;
}

Vector3 GeometryObject::getPosition() const {
    return position;
}

Vector3 GeometryObject::getNormal(const Vector3 &coordinate) const {
    throw std::invalid_argument("not implemented");
}

double GeometryObject::intersectDistance(const Vector3 &from, const Vector3 &direction) const {
    throw std::invalid_argument("not implemented");
}

Vector3 GeometryObject::intersect(const Vector3 &from, const Vector3 &direction) const {
    throw std::invalid_argument("not implemented");
}

void GeometryObject::setMaterial(MaterialBase* inMaterial) {
    this->material = inMaterial;
}

MaterialBase* GeometryObject::getMaterial() const {
    return material;
}
