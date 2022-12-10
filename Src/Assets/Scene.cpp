//
// Created by luoli on 2022/9/24.
//

#include "Scene.h"
#include "Objects/Sphere.h"

bool Scene::hitTest(const Vector3 &from, const Vector3 &direction) {
    for(GeometryObject *obj : objects){
        if(obj->intersectDistance(from, direction) != INT_MIN)
            return true;
    }

    return false;
}

GeometryObject* Scene::getHitObject(const Vector3 &from, const Vector3 &direction) const {
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

GeometryObject *Scene::getNearestLightSource(const Vector3 &from) const {
    double minT = INT_MAX;
    GeometryObject* resultObj = nullptr;

    for(GeometryObject *obj : objects){
        if(obj->getMaterial()->getEmission() == Vector3::INF())
            continue;

        Vector3 toLightDirection = obj->getPosition() - from;
        toLightDirection.normalize();

        double objT = obj->intersectDistance(from, toLightDirection);

        if(objT != INT_MIN){
            if(isPathBlocked(from, toLightDirection, obj)) continue;

            double absObjT = abs(objT);

            if(absObjT < minT){
                minT = absObjT;
                resultObj = obj;
            }
        }
    }

    return resultObj;
}

bool Scene::isPathBlocked(const Vector3 &from, const Vector3 &direction, const GeometryObject *target) const {
    GeometryObject* hitObject = getHitObject(from, direction);

    if(hitObject == nullptr)
        return false;

    return target != hitObject;
}
