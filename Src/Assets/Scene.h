//
// Created by luoli on 2022/9/24.
//

#ifndef COMPUTERGRAPHICS_SCENE_H
#define COMPUTERGRAPHICS_SCENE_H


#include <vector>
#include "Objects/GeometryObject.h"
#include "Materials/Diffusion.h"

class Scene {
private:
    std::vector<GeometryObject*> objects;
public:
    bool hitTest(const Vector3 &from, const Vector3 &direction);
    [[nodiscard]] GeometryObject* getHitObject(const Vector3 &from, const Vector3 &direction) const;
    [[nodiscard]] GeometryObject* getNearestLightSource(const Vector3 &from) const;
    [[nodiscard]] bool isPathBlocked(const Vector3 &from, const Vector3 &direction, const GeometryObject* target) const;
    void addObject(GeometryObject *object);
    [[nodiscard]] std::vector<GeometryObject*> getObjects() const;
};


#endif //COMPUTERGRAPHICS_SCENE_H
