//
// Created by luoli on 2022/9/22.
//

#include "Sphere.h"
#include "../../Utils/Random.h"
#include <cmath>

Sphere::Sphere(const Vector3 &coordinate, double radius, MaterialBase* material) : GeometryObject(coordinate) {
    this->radius = radius;
    this->setMaterial(material);
}

Vector3 Sphere::getNormal(const Vector3 &coordinate) const {
    Vector3 result = coordinate - position;
    //result.normalize();

    return result;
}

double Sphere::intersectDistance(const Vector3 &from, const Vector3 &direction) const {
    Vector3 L = position - from;
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

Vector3 Sphere::intersect(const Vector3 &from, const Vector3 &direction) const {
    double t = intersectDistance(from, direction);

    return t * direction;
}

Vector3 Sphere::getRandomPoint(const Vector3 &origin) const {
    double r1 = Random::next();
    double r2 = Random::next();
    double distanceSquared = pow(getNormal(origin).magnitude(), 2);
    double z = 1 + r2 * (sqrt(1 - radius * radius/distanceSquared) - 1);
    double phi = 2 * M_PI * r1;
    double x = cos(phi) * sqrt(1 - z * z);
    double y = sin(phi) * sqrt(1 - z * z);

    return {x, y, z};
}

double Sphere::getProbabilityDensity(const Vector3 &origin, const Vector3 &direction) const {
    if(intersectDistance(origin, direction) == INT_MIN) return 0;

    double cos_theta_max = sqrt(1- radius * radius / pow((position - origin).magnitude(), 2));
    double solid_angle = 2 * M_PI * (1 - cos_theta_max);

    return 1.0 / solid_angle;
}
