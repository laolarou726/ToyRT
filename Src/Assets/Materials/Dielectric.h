//
// Created by luoli on 2022/12/7.
//

#ifndef TOYRT_DIELECTRIC_H
#define TOYRT_DIELECTRIC_H


#include "MaterialBase.h"

class Dielectric : public MaterialBase{
private:
    double refractiveIndex;
public:
    explicit Dielectric(double refractiveIndex);
    static double schlick(double cosine, double refractiveIndex);
    static Vector3 refract(const Vector3 &inRay, const Vector3 &meshNormal, double factor);
    Vector3 getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) override;
};


#endif //TOYRT_DIELECTRIC_H
