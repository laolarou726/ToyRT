//
// Created by luoli on 2022/9/16.
//

#include "Ray.h"
#include "Materials/Reflection.h"

Ray::Ray(const Tuple &direction, int maxBounces) {
    this->maxBounces = maxBounces;

    auto d = Tuple(direction);
    d.normalize();

    this->direction = d;
}

Ray::Ray(const Tuple &origin, const Tuple &direction, int maxBounces) {
    this->maxBounces = maxBounces;

    auto d = Tuple(direction);
    d.normalize();

    this->origin = origin;
    this->direction = d;
}

Tuple Ray::emit(const Scene &scene) {
    Tuple result = Tuple::zero();
    Tuple whole = Tuple::one();
    int bounceCount = 0;
    GeometryObject* lastHitObject;

    while(bounceCount < maxBounces){
        GeometryObject* hitObject = scene.getHitObject(origin, direction);

        if(hitObject == nullptr) break;
        if(hitObject == lastHitObject) break;

        lastHitObject = hitObject;
        Tuple hitDirection = hitObject->intersect(origin, direction);

        //Tuple hitDirection = hitObject->intersect(origin, direction);

        origin = origin + hitDirection;

        Tuple normal = hitObject->getNormal(origin);
        MaterialBase* mat = hitObject->getMaterial();
        Tuple nextDirection = hitObject->getMaterial()->getOutRayDirection(direction, normal);

        if(dynamic_cast<Reflection*>(mat) == nullptr){
            if(mat->getEmission() != Tuple::INF()){
                result = result + mat->getEmission().vectorDot(whole);
            }
            else{
                GeometryObject* nearestLight = scene.getNearestLightSource(origin, normal);

                if(nearestLight != nullptr){
                    if(!scene.isPathBlocked(origin, normal, nearestLight)){

                    }
                }
            }

            whole = whole.vectorDot(mat->getReflectance());
        }

        direction = nextDirection;
        bounceCount++;
    }

    return result;
}
