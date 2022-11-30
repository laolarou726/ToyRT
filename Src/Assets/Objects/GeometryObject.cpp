//
// Created by luoli on 2022/9/22.
//

#include "GeometryObject.h"

GeometryObject::GeometryObject(const Tuple &position) {
    this->position = position;
}

Tuple GeometryObject::getPosition() const {
    return position;
}

Tuple GeometryObject::getNormal(const Tuple &coordinate) const {
    throw std::invalid_argument("not implemented");
}

double GeometryObject::intersectDistance(const Tuple &from, const Tuple &direction) const {
    throw std::invalid_argument("not implemented");
}

Tuple GeometryObject::intersect(const Tuple &from, const Tuple &direction) const {
    throw std::invalid_argument("not implemented");
}

void GeometryObject::setMaterial(MaterialBase* inMaterial) {
    this->material = inMaterial;
}

MaterialBase* GeometryObject::getMaterial() const {
    return material;
}
