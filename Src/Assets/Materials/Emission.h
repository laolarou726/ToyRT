//
// Created by luoli on 2022/10/20.
//

#ifndef COMPUTERGRAPHICS_EMISSION_H
#define COMPUTERGRAPHICS_EMISSION_H


#include "MaterialBase.h"

class Emission : public MaterialBase{
public:
    explicit Emission(const Tuple &reflectance);
    explicit Emission(const Tuple &reflectance, const Tuple &emission);
    Tuple getOutRayDirection(const Tuple &inRay, const Tuple &meshNormal) override;
};


#endif //COMPUTERGRAPHICS_EMISSION_H
