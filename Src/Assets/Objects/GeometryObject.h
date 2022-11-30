//
// Created by luoli on 2022/9/22.
//

#ifndef COMPUTERGRAPHICS_GEOMETRYOBJECT_H
#define COMPUTERGRAPHICS_GEOMETRYOBJECT_H


#include "../../Tuple.h"
#include "../Materials/MaterialBase.h"

class GeometryObject {
protected:
    Tuple position;
    MaterialBase* material;
public:
    explicit GeometryObject(const Tuple &position);
    [[nodiscard]] virtual Tuple getPosition() const;
    [[nodiscard]] virtual Tuple getNormal(const Tuple &coordinate) const;
    [[nodiscard]] virtual double intersectDistance(const Tuple &from, const Tuple &direction) const;
    [[nodiscard]] virtual Tuple intersect(const Tuple &from, const Tuple &direction) const;
    virtual void setMaterial(MaterialBase *inMaterial);
    [[nodiscard]] virtual MaterialBase* getMaterial() const;
    [[nodiscard]] virtual Tuple getRandomPoint(const Tuple &origin) const = 0;
    [[nodiscard]] virtual double getProbabilityDensity(const Tuple &origin, const Tuple &direction) const = 0;
};


#endif //COMPUTERGRAPHICS_GEOMETRYOBJECT_H
