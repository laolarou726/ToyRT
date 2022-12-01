//
// Created by luoli on 2022/10/12.
//

#ifndef COMPUTERGRAPHICS_REFLECTION_H
#define COMPUTERGRAPHICS_REFLECTION_H


#include "MaterialBase.h"

class Reflection : public MaterialBase {
public:
    explicit Reflection(const Vector3 &reflectance);
    Vector3 getOutRayDirection(const Vector3& InRayDirection, const Vector3&  MeshNormal) override;
};


#endif //COMPUTERGRAPHICS_REFLECTION_H
