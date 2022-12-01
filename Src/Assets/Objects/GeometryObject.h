//
// Created by luoli on 2022/9/22.
//

#ifndef COMPUTERGRAPHICS_GEOMETRYOBJECT_H
#define COMPUTERGRAPHICS_GEOMETRYOBJECT_H


#include "../../Models/Vector3.h"
#include "../Materials/MaterialBase.h"

class GeometryObject {
protected:
    Vector3 position;
    MaterialBase* material;
public:
    explicit GeometryObject(const Vector3 &position);
    [[nodiscard]] virtual Vector3 getPosition() const;
    [[nodiscard]] virtual Vector3 getNormal(const Vector3 &coordinate) const;
    [[nodiscard]] virtual double intersectDistance(const Vector3 &from, const Vector3 &direction) const;
    [[nodiscard]] virtual Vector3 intersect(const Vector3 &from, const Vector3 &direction) const;
    virtual void setMaterial(MaterialBase *inMaterial);
    [[nodiscard]] virtual MaterialBase* getMaterial() const;
    [[nodiscard]] virtual Vector3 getRandomPoint(const Vector3 &origin) const = 0;
    [[nodiscard]] virtual double getProbabilityDensity(const Vector3 &origin, const Vector3 &direction) const = 0;
};


#endif //COMPUTERGRAPHICS_GEOMETRYOBJECT_H
