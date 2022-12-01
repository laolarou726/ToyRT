//
// Created by luoli on 2022/9/24.
//

#include "Plane.h"

Plane::Plane(const Vector3 &point, const Vector3 &normal, MaterialBase* material) : GeometryObject({INT_MIN, INT_MIN, INT_MIN}) {
    this->point = point;

    Vector3 n = normal;
    n.normalize();

    this->normal = n;
    this->setMaterial(material);
}

Vector3 Plane::getNormal(const Vector3 &coordinate) const {
    return normal;
}

Vector3 Plane::getPoint() const {
    return point;
}

double Plane::intersectDistance(const Vector3 &from, const Vector3 &direction) const {
    double dot = normal.dot(direction);

    if(dot >= 0)
        return INT_MIN;

    auto fromPos = Vector3(from);
    double t = (point - fromPos).dot(normal) / dot;

    return t;
}

Vector3 Plane::intersect(const Vector3 &from, const Vector3 &direction) const {
    double t = intersectDistance(from, direction);

    if(t == INT_MIN)
        return Vector3::INF();

    Vector3 at = t * direction;

    return at;
}

Vector3 Plane::getRandomPoint(const Vector3 &origin) const {
    return Vector3::INF();
}

double Plane::getProbabilityDensity(const Vector3 &origin, const Vector3 &direction) const {
    return INT_MIN;
}
