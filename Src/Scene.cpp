//
// Created by luoli on 2022/9/24.
//

#include "Scene.h"
#include "Assets/Objects/Sphere.h"

bool Scene::hitTest(const Tuple &from, const Tuple &direction) {
    for(GeometryObject *obj : objects){
        if(obj->intersectDistance(from, direction) != INT_MIN)
            return true;
    }

    return false;
}

GeometryObject* Scene::getHitObject(const Tuple &from, const Tuple &direction) const {
    double minT = INT_MAX;
    GeometryObject* resultObj = nullptr;

    for(GeometryObject *obj : objects){
        double objT = obj->intersectDistance(from, direction);

        if(objT != INT_MIN){
            double absObjT = abs(objT);

            if(absObjT < minT){
                minT = absObjT;
                resultObj = obj;
            }
        }
    }

    return resultObj;
}

void Scene::addObject(GeometryObject *object) {
    objects.emplace_back(object);
}

std::vector<GeometryObject*> Scene::getObjects() const {
    return objects;
}

GeometryObject *Scene::getNearestLightSource(const Tuple &from, const Tuple &direction) const {
    double minT = INT_MAX;
    GeometryObject* resultObj = nullptr;

    for(GeometryObject *obj : objects){
        if(obj->getMaterial()->getEmission() == Tuple::INF())
            continue;

        double objT = obj->intersectDistance(from, direction);

        if(objT != INT_MIN){
            double absObjT = abs(objT);

            if(absObjT < minT){
                minT = absObjT;
                resultObj = obj;
            }
        }
    }

    return resultObj;
}

bool Scene::isPathBlocked(const Tuple &from, const Tuple &direction, const GeometryObject *target) const {
    GeometryObject* hitObject = getHitObject(from, direction);

    if(hitObject == nullptr)
        return false;

    return target != hitObject;
}
