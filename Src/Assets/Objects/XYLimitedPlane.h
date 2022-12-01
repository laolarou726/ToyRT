//
// Created by luoli on 2022/10/19.
//

#ifndef COMPUTERGRAPHICS_XYLIMITEDPLANE_H
#define COMPUTERGRAPHICS_XYLIMITEDPLANE_H


#include "GeometryObject.h"
#include "../Materials/Diffusion.h"

class XYLimitedPlane : public GeometryObject {
private:
    Vector3 point;
    Vector3 normal;
    double side;
public:
    XYLimitedPlane(const Vector3 &point, const Vector3 &normal, double side, MaterialBase* material = Diffusion::DEFAULT());
    [[nodiscard]] Vector3 getNormal(const Vector3 &coordinate) const override;
    [[nodiscard]] double intersectDistance(const Vector3 &from, const Vector3 &direction) const override;
    [[nodiscard]] Vector3 intersect(const Vector3 &from, const Vector3 &direction) const override;
    [[nodiscard]] Vector3 getPoint() const;
    [[nodiscard]] double getSide() const;

    [[nodiscard]] Vector3 getRandomPoint(const Vector3 &origin) const override;
    [[nodiscard]] double getProbabilityDensity(const Vector3 &origin, const Vector3 &direction) const override;
};


#endif //COMPUTERGRAPHICS_XYLIMITEDPLANE_H
