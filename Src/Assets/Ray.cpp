//
// Created by luoli on 2022/9/16.
//

#include "Ray.h"
#include "Materials/Reflection.h"

Ray::Ray(const Vector3 &direction, int maxBounces) {
    this->maxBounces = maxBounces;

    auto d = Vector3(direction);
    d.normalize();

    this->direction = d;
}

Ray::Ray(const Vector3 &origin, const Vector3 &direction, int maxBounces) {
    this->maxBounces = maxBounces;

    auto d = Vector3(direction);
    d.normalize();

    this->origin = origin;
    this->direction = d;
}

Vector3 Ray::emit(const Scene &scene) {
    Vector3 result = Vector3::zero();
    Vector3 whole = Vector3::one();
    int bounceCount = 0;
    GeometryObject* lastHitObject;

    while(bounceCount < maxBounces){
        GeometryObject* hitObject = scene.getHitObject(origin, direction);

        if(hitObject == nullptr) break;
        if(hitObject == lastHitObject) break;

        lastHitObject = hitObject;
        Vector3 hitDirection = hitObject->intersect(origin, direction);

        //Vector3 hitDirection = hitObject->intersect(origin, direction);

        origin = origin + hitDirection;

        Vector3 normal = hitObject->getNormal(origin);
        MaterialBase* mat = hitObject->getMaterial();
        Vector3 nextDirection = hitObject->getMaterial()->getOutRayDirection(direction, normal);

        if(dynamic_cast<Reflection*>(mat) == nullptr){
            if(mat->getEmission() != Vector3::INF()){
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
