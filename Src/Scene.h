//
// Created by luoli on 2022/9/24.
//

#ifndef COMPUTERGRAPHICS_SCENE_H
#define COMPUTERGRAPHICS_SCENE_H


#include <vector>
#include "Assets/Objects/GeometryObject.h"
#include "Assets/Materials/Diffusion.h"

class Scene {
private:
    std::vector<GeometryObject*> objects;
public:
    bool hitTest(const Tuple &from, const Tuple &direction);
    [[nodiscard]] GeometryObject* getHitObject(const Tuple &from, const Tuple &direction) const;
    [[nodiscard]] GeometryObject* getNearestLightSource(const Tuple &from, const Tuple &direction) const;
    [[nodiscard]] bool isPathBlocked(const Tuple &from, const Tuple &direction, const GeometryObject* target) const;
    void addObject(GeometryObject *object);
    [[nodiscard]] std::vector<GeometryObject*> getObjects() const;
};


#endif //COMPUTERGRAPHICS_SCENE_H
