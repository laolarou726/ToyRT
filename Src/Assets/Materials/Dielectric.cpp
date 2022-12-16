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
    bool isFromInsideToOutside = inRay.dot(meshNormal) > 0;

    // inside to outside.
    if (isFromInsideToOutside)
    {
        outwardNormal = -1 * meshNormal;
        factor = this->refractiveIndex;
    }
    // outside to inside.
    else
    {
        outwardNormal = meshNormal;
        factor = 1.0 / this->refractiveIndex;
    }

    Vector3 reflected = inRay - meshNormal * (inRay.dot(meshNormal)) * 2.0;
    auto [refracted, cosine] = refract(inRay, outwardNormal, factor);
    double reflectProbability;

    if (refracted != Vector3::INF())
    {
        reflectProbability = schlick(cosine, this->refractiveIndex);
    }
    else
    {
        reflectProbability = 1;
    }

    if(Random::next() < reflectProbability){
        return reflected;
    }
    else{
        return refracted;
    }
}

tuple<Vector3, double> Dielectric::refract(const Vector3 &inRay, const Vector3 &meshNormal, double factor) {

    double sine = factor * meshNormal.cross(inRay).magnitude();
    double cosine = sqrt(1 - pow(sine, 2));

    return {inRay.cross(meshNormal).cross(meshNormal) * sine + (-1 * meshNormal) * cosine, cosine};

}

double Dielectric::schlick(double cosine, double refractiveIndex) {

    double r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
    r0 = pow(r0, 2);

    return r0 + (1.0 - r0) * pow(1 - cosine, 5);

}
