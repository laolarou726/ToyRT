//
// Created by luoli on 2022/10/20.
//

#ifndef COMPUTERGRAPHICS_EMISSION_H
#define COMPUTERGRAPHICS_EMISSION_H


#include "MaterialBase.h"

class Emission : public MaterialBase{
public:
    explicit Emission(const Vector3 &reflectance);
    explicit Emission(const Vector3 &reflectance, const Vector3 &emission);
    Vector3 getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) override;
};


#endif //COMPUTERGRAPHICS_EMISSION_H
