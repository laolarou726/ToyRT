//
// Created by luoli on 2022/9/25.
//

#ifndef COMPUTERGRAPHICS_MATERIALBASE_H
#define COMPUTERGRAPHICS_MATERIALBASE_H


#include "../../Tuple.h"
#include <tuple>

class MaterialBase {
protected:
    Tuple emission = {INT_MIN, INT_MIN, INT_MIN};
    Tuple reflectance;
public:
    [[nodiscard]] Tuple getEmission() const;
    [[nodiscard]] Tuple getReflectance() const;
    virtual Tuple getOutRayDirection(const Tuple& inRay, const Tuple& meshNormal);
    [[nodiscard]] virtual tuple<char, char, char> getReflectanceColor() const;
};


#endif //COMPUTERGRAPHICS_MATERIALBASE_H
