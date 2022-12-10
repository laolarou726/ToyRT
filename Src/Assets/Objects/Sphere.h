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
    Sphere(const Vector3 &coordinate, double radius, MaterialBase* material = Diffusion::DEFAULT());
    [[nodiscard]] Vector3 getNormal(const Vector3 &coordinate) const override;
    [[nodiscard]] double intersectDistance(const Vector3 &from, const Vector3 &direction) const override;
    [[nodiscard]] Vector3 intersect(const Vector3 &from, const Vector3 &direction) const override;

    [[nodiscard]] Vector3 getRandomPoint(const Vector3 &origin) const override;
    [[nodiscard]] double getProbabilityDensity(const Vector3 &origin, const Vector3 &direction) const override;

    static Vector3 randomInUnitSphere();
};


#endif //COMPUTERGRAPHICS_SPHERE_H
