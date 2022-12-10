//
// Created by luoli on 2022/10/19.
//

#include "XYLimitedPlane.h"
#include "../../Utils/Random.h"

XYLimitedPlane::XYLimitedPlane(const Vector3 &point, const Vector3 &normal, double side, MaterialBase* material) : GeometryObject(point){
    this->point = point;

    Vector3 n = normal;
    n.normalize();

    this->normal = n;
    this->side = side;
    this->setMaterial(material);
}

Vector3 XYLimitedPlane::getNormal(const Vector3 &coordinate) const {
    return normal;
}

double XYLimitedPlane::intersectDistance(const Vector3 &from, const Vector3 &direction) const {
    double dot = normal.dot(direction);

    if(dot >= 0)
        return INT_MIN;

    auto fromPos = Vector3(from);
    double t = (point - fromPos).dot(normal) / dot;

    if(abs((from + t * direction - point).x) > side / 2 ||
        abs((from + t * direction - point).y) > side / 2)
        return INT_MIN;

    return t;
}

Vector3 XYLimitedPlane::intersect(const Vector3 &from, const Vector3 &direction) const {
    double t = intersectDistance(from, direction);

    if(t == INT_MIN)
        return Vector3::INF();

    Vector3 at = from + t * direction;

    return at;
}

Vector3 XYLimitedPlane::getPoint() const {
    return point;
}

double XYLimitedPlane::getSide() const {
    return side;
}

Vector3 XYLimitedPlane::getRandomPoint(const Vector3 &origin) const {
    Vector3 center = point;
    Vector3 leftCorner = Vector3::zero();

    leftCorner.x = center.x - side / 2;
    leftCorner.y = center.y - side / 2;
    leftCorner.z = center.z;

    return {leftCorner.x + side * Random::next(),
            leftCorner.y + side * Random::next(),
            leftCorner.z};
}

double XYLimitedPlane::getProbabilityDensity(const Vector3 &origin, const Vector3 &direction) const {
    if(intersectDistance(origin, direction) == INT_MIN) return 0;

    double area = pow(side, 2);
    double distanceSquared = pow(direction.magnitude(), 2);
    double cosine = fabs(direction.dot(normal) / direction.magnitude());

    return distanceSquared / (cosine * area);
}
