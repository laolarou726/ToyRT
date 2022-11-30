//
// Created by luoli on 2022/9/22.
//

#ifndef COMPUTERGRAPHICS_SPHERE_H
#define COMPUTERGRAPHICS_SPHERE_H


#include "GeometryObject.h"
#include "../Materials/Diffusion.h"

class Sphere : public GeometryObject {
private:
    double radius;
public:
    Sphere(const Tuple &coordinate, double radius, MaterialBase* material = Diffusion::DEFAULT());
    [[nodiscard]] Tuple getNormal(const Tuple &coordinate) const override;
    [[nodiscard]] double intersectDistance(const Tuple &from, const Tuple &direction) const override;
    [[nodiscard]] Tuple intersect(const Tuple &from, const Tuple &direction) const override;

    [[nodiscard]] Tuple getRandomPoint(const Tuple &origin) const override;
    [[nodiscard]] double getProbabilityDensity(const Tuple &origin, const Tuple &direction) const override;
};


#endif //COMPUTERGRAPHICS_SPHERE_H
