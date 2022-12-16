//
// Created by luoli on 2022/9/25.
//

#ifndef COMPUTERGRAPHICS_MATERIALBASE_H
#define COMPUTERGRAPHICS_MATERIALBASE_H


#include "../../Models/Vector3.h"
#include <tuple>

class MaterialBase {
protected:
    Vector3 emission = {INT_MIN, INT_MIN, INT_MIN};
    Vector3 reflectance;
public:
    [[nodiscard]] Vector3 getEmission() const;
    [[nodiscard]] Vector3 getReflectance() const;
    virtual Vector3 getOutRayDirection(const Vector3& inRay, const Vector3& meshNormal);
    virtual double scatteringPDF(const Vector3& inRay, const Vector3& meshNormal);
    [[nodiscard]] virtual tuple<char, char, char> getReflectanceColor() const;
};


#endif //COMPUTERGRAPHICS_MATERIALBASE_H
