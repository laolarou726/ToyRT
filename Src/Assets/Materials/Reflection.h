//
// Created by luoli on 2022/10/12.
//

#ifndef COMPUTERGRAPHICS_REFLECTION_H
#define COMPUTERGRAPHICS_REFLECTION_H


#include "MaterialBase.h"

class Reflection : public MaterialBase {
public:
    explicit Reflection(const Tuple &reflectance);
    Tuple getOutRayDirection(const Tuple& InRayDirection, const Tuple&  MeshNormal) override;
};


#endif //COMPUTERGRAPHICS_REFLECTION_H
