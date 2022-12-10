//
// Created by luoli on 2022/9/22.
//

#include "Sphere.h"
#include <cmath>
#include <cfloat>

Sphere::Sphere(const Vector3 &coordinate, double radius, MaterialBase* material) : GeometryObject(coordinate) {
    this->radius = radius;
    this->setMaterial(material);
}

Vector3 Sphere::getNormal(const Vector3 &coordinate) const {
    Vector3 result = coordinate - position;
    result.normalize();

    return result;
}

double Sphere::intersectDistance(const Vector3 &from, const Vector3 &direction) const {
    Vector3 oc = from - position;
    double a = direction.dot(direction);
    double b = oc.dot(direction);
    double c = oc.dot(oc) - pow(radius, 2);

    // discriminant
    double discriminant = pow(b, 2) - a * c;

    if (discriminant > 0)
    {
        double sqrtDiscriminant = sqrt(discriminant);
        double temp = (-b - sqrtDiscriminant) / a;

        if (temp >= DBL_MAX || temp <= 0.001)
        {
            temp = (-b + sqrtDiscriminant)  / a;

            if (temp >= DBL_MAX || temp <= 0.001)
            {
                return INT_MIN;
            }
        }

        return temp;
    }

    return INT_MIN;
}

Vector3 Sphere::intersect(const Vector3 &from, const Vector3 &direction) const {
    double t = intersectDistance(from, direction);

    return from + t * direction;
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

Vector3 Sphere::randomInUnitSphere() {
    Vector3 result;

    do
    {
        result = Vector3(Random::next(), Random::next(), Random::next()) * 2 - Vector3::one();
    } while (result.magnitude() >= 1);

    return result;
}
