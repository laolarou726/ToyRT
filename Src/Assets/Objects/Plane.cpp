//
// Created by luoli on 2022/9/24.
//

#include "Plane.h"

Plane::Plane(const Tuple &point, const Tuple &normal, MaterialBase* material) : GeometryObject({INT_MIN, INT_MIN, INT_MIN}) {
    this->point = point;

    Tuple n = normal;
    n.normalize();

    this->normal = n;
    this->setMaterial(material);
}

Tuple Plane::getNormal(const Tuple &coordinate) const {
    return normal;
}

Tuple Plane::getPoint() const {
    return point;
}

double Plane::intersectDistance(const Tuple &from, const Tuple &direction) const {
    double dot = normal.dot(direction);

    if(dot >= 0)
        return INT_MIN;

    auto fromPos = Tuple(from);
    double t = (point - fromPos).dot(normal) / dot;

    return t;
}

Tuple Plane::intersect(const Tuple &from, const Tuple &direction) const {
    double t = intersectDistance(from, direction);

    if(t == INT_MIN)
        return Tuple::INF();

    Tuple at = t * direction;

    return at;
}

Tuple Plane::getRandomPoint(const Tuple &origin) const {
    return Tuple::INF();
}

double Plane::getProbabilityDensity(const Tuple &origin, const Tuple &direction) const {
    return INT_MIN;
}
