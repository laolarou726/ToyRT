//
// Created by luoli on 2022/12/7.
//

#include "Dielectric.h"

Dielectric::Dielectric(double refractiveIndex) {
    this->refractiveIndex = refractiveIndex;
    this->reflectance = Vector3::one();
}

Vector3 Dielectric::getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) {
    Vector3 outwardNormal;
    double factor;
    double cosine;

    // inside to outside.
    if (inRay.dot(meshNormal) > 0)
    {
        outwardNormal = -1 * meshNormal;
        factor = this->refractiveIndex;
        cosine = this->refractiveIndex * inRay.dot(meshNormal) / inRay.magnitude();
    }
    // outside to inside.
    else
    {
        outwardNormal = meshNormal;
        factor = 1.0 / this->refractiveIndex;
        cosine = -1 * (inRay.dot(meshNormal)) / inRay.magnitude();
    }

    Vector3 reflected = inRay - meshNormal * (inRay.dot(meshNormal)) * 2.0f;
    Vector3 refracted = refract(inRay, outwardNormal, factor);

    double reflectProbability;
    if (refracted != Vector3::INF())
    {
        reflectProbability = schlick(cosine, this->refractiveIndex);
    }
    else
    {
        reflectProbability = 1;
    }

    return Random::next() < reflectProbability ? reflected : refracted;
}

Vector3 Dielectric::refract(const Vector3 &inRay, const Vector3 &meshNormal, double factor) {
    Vector3 uv = inRay;
    uv.normalize();

    double dt = uv.dot(meshNormal);
    double discriminant = 1 - pow(factor, 2) * (1 - pow(dt, 2));

    if(discriminant > 0){
        return (uv - meshNormal * dt) * factor - meshNormal * sqrt(discriminant);
    }

    return Vector3::INF();
}

double Dielectric::schlick(double cosine, double refractiveIndex) {
    double r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = pow(r0, 2);

    return r0 + (1 - r0) * pow((1 - cosine), 5);
}
