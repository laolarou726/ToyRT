//
// Created by luoli on 2022/10/19.
//

#ifndef COMPUTERGRAPHICS_XYLIMITEDPLANE_H
#define COMPUTERGRAPHICS_XYLIMITEDPLANE_H


#include "GeometryObject.h"
#include "../Materials/Diffusion.h"

class XYLimitedPlane : public GeometryObject {
private:
    Tuple point;
    Tuple normal;
    double side;
public:
    XYLimitedPlane(const Tuple &point, const Tuple &normal, double side, MaterialBase* material = Diffusion::DEFAULT());
    [[nodiscard]] Tuple getNormal(const Tuple &coordinate) const override;
    [[nodiscard]] double intersectDistance(const Tuple &from, const Tuple &direction) const override;
    [[nodiscard]] Tuple intersect(const Tuple &from, const Tuple &direction) const override;
    [[nodiscard]] Tuple getPoint() const;
    [[nodiscard]] double getSide() const;

    [[nodiscard]] Tuple getRandomPoint(const Tuple &origin) const override;
    [[nodiscard]] double getProbabilityDensity(const Tuple &origin, const Tuple &direction) const override;
};


#endif //COMPUTERGRAPHICS_XYLIMITEDPLANE_H
