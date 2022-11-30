//
// Created by luoli on 2022/9/22.
//

#include "Sphere.h"
#include "../../Random.h"
#include <cmath>

Sphere::Sphere(const Tuple &coordinate, double radius, MaterialBase* material) : GeometryObject(coordinate) {
    this->radius = radius;
    this->setMaterial(material);
}

Tuple Sphere::getNormal(const Tuple &coordinate) const {
    Tuple result = coordinate - position;
    //result.normalize();

    return result;
}

double Sphere::intersectDistance(const Tuple &from, const Tuple &direction) const {
    Tuple L = position - from;
    double t_ca = L.dot(direction);

    if (t_ca < 0) return INT_MIN;

    double dSquare = L.dot(L) - pow(t_ca, 2);
    if (dSquare > pow(radius, 2))
    {
        return INT_MIN;
    }

    double d = sqrt(dSquare);
    double t_hc = sqrt(pow(radius, 2) - pow(d, 2));
    double t_0 = t_ca - t_hc;

    return t_0;
}

Tuple Sphere::intersect(const Tuple &from, const Tuple &direction) const {
    double t = intersectDistance(from, direction);

    return t * direction;
}

Tuple Sphere::getRandomPoint(const Tuple &origin) const {
    double r1 = Random::next();
    double r2 = Random::next();
    double distanceSquared = pow(getNormal(origin).magnitude(), 2);
    double z = 1 + r2 * (sqrt(1 - radius * radius/distanceSquared) - 1);
    double phi = 2 * M_PI * r1;
    double x = cos(phi) * sqrt(1 - z * z);
    double y = sin(phi) * sqrt(1 - z * z);

    return {x, y, z};
}

double Sphere::getProbabilityDensity(const Tuple &origin, const Tuple &direction) const {
    if(intersectDistance(origin, direction) == INT_MIN) return 0;

    double cos_theta_max = sqrt(1- radius * radius / pow((position - origin).magnitude(), 2));
    double solid_angle = 2 * M_PI * (1 - cos_theta_max);

    return 1.0 / solid_angle;
}
