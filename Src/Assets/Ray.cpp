//
// Created by luoli on 2022/9/16.
//

#include "Ray.h"
#include "Materials/Reflection.h"
#include "Materials/Dielectric.h"

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
    //GeometryObject* lastHitObject;

    while(bounceCount < maxBounces){
        GeometryObject* hitObject = scene.getHitObject(origin, direction);

        if(hitObject == nullptr) break;

        //if(hitObject == lastHitObject) break;
        //lastHitObject = hitObject;

        MaterialBase* mat = hitObject->getMaterial();

        Vector3 hitDirection = hitObject->intersect(origin, direction);
        origin = hitDirection;

        Vector3 normal = hitObject->getNormal(origin);

        Vector3 nextDirection = hitObject->getMaterial()->getOutRayDirection(direction, normal);
        //nextDirection.normalize();

        if(mat->getEmission() != Vector3::INF()){
            result = result + mat->getEmission().vectorDot(whole);
        }

        whole = whole.vectorDot(mat->getReflectance());
        direction = nextDirection;
        bounceCount++;

        /*
        if(dynamic_cast<Diffusion*>(mat) == nullptr)
            continue;

        GeometryObject* nearestLight = scene.getNearestLightSource(origin);

        if(nearestLight == nullptr)
            continue;

        Vector3 randomSurfacePoint = hitObject->getRandomPoint(origin);
        Vector3 toLightDirection = nearestLight->getPosition() - randomSurfacePoint;
        toLightDirection.normalize();

        double pdf = normal.dot(direction) / M_PI; //hitObject->getProbabilityDensity(origin, toLightDirection);
        double scatterPDF = mat->scatteringPDF(direction, normal);

        result = result + (mat->getReflectance() * scatterPDF) / pdf;
        result = result * 0.3;
         */
    }

    return result;
}
