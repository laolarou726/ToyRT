//
// Created by luoli on 2022/9/24.
//

#ifndef COMPUTERGRAPHICS_PLANE_H
#define COMPUTERGRAPHICS_PLANE_H


#include "GeometryObject.h"
#include "../Materials/Diffusion.h"

class Plane : public GeometryObject {
private:
    Tuple point;
    Tuple normal;
public:
    Plane(const Tuple &point, const Tuple &normal, MaterialBase *material = Diffusion::DEFAULT());
    [[nodiscard]] Tuple getNormal(const Tuple &coordinate) const override;
    [[nodiscard]] double intersectDistance(const Tuple &from, const Tuple &direction) const override;
    [[nodiscard]] Tuple intersect(const Tuple &from, const Tuple &direction) const override;
    [[nodiscard]] Tuple getPoint() const;

    [[nodiscard]] Tuple getRandomPoint(const Tuple &origin) const override;
    [[nodiscard]] double getProbabilityDensity(const Tuple &origin, const Tuple &direction) const override;
};


#endif //COMPUTERGRAPHICS_PLANE_H
