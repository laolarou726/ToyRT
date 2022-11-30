//
// Created by luoli on 2022/10/19.
//

#include "XYLimitedPlane.h"
#include "../../Random.h"

XYLimitedPlane::XYLimitedPlane(const Tuple &point, const Tuple &normal, double side, MaterialBase* material) : GeometryObject({INT_MIN, INT_MIN, INT_MIN}){
    this->point = point;

    Tuple n = normal;
    n.normalize();

    this->normal = n;
    this->side = side;
    this->setMaterial(material);
}

Tuple XYLimitedPlane::getNormal(const Tuple &coordinate) const {
    return normal;
}

double XYLimitedPlane::intersectDistance(const Tuple &from, const Tuple &direction) const {
    double dot = normal.dot(direction);

    if(dot >= 0)
        return INT_MIN;

    auto fromPos = Tuple(from);
    double t = (point - fromPos).dot(normal) / dot;

    if(abs((from + t * direction - point).x) > side / 2 ||
        abs((from + t * direction - point).y) > side / 2)
        return INT_MIN;

    return t;
}

Tuple XYLimitedPlane::intersect(const Tuple &from, const Tuple &direction) const {
    double t = intersectDistance(from, direction);

    if(t == INT_MIN)
        return Tuple::INF();

    Tuple at = t * direction;

    return at;
}

Tuple XYLimitedPlane::getPoint() const {
    return point;
}

double XYLimitedPlane::getSide() const {
    return side;
}

Tuple XYLimitedPlane::getRandomPoint(const Tuple &origin) const {
    Tuple center = point;
    Tuple leftCorner = Tuple::zero();

    leftCorner.x = center.x - side / 2;
    leftCorner.y = center.y - side / 2;
    leftCorner.z = center.z;

    return {leftCorner.x + side * Random::next(),
            leftCorner.y + side * Random::next(),
            leftCorner.z};
}

double XYLimitedPlane::getProbabilityDensity(const Tuple &origin, const Tuple &direction) const {
    if(intersectDistance(origin, direction) == INT_MIN) return 0;

    double area = pow(side, 2);
    double distanceSquared = pow(direction.magnitude(), 2);
    double cosine = fabs(direction.dot(normal) / direction.magnitude());

    return distanceSquared / (cosine * area);
}
