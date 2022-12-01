//
// Created by luoli on 2022/9/16.
//

#ifndef COMPUTERGRAPHICS_RAY_H
#define COMPUTERGRAPHICS_RAY_H


#include "../Models/Vector3.h"
#include "Scene.h"

class Ray {
private:
    int maxBounces;
public:
    Vector3 origin;
    Vector3 direction;

    explicit Ray(const Vector3 &direction, int maxBounces = 4);
    explicit Ray(const Vector3 &origin, const Vector3 &direction, int maxBounces = 4);
    virtual Vector3 emit(const Scene &scene);
};


#endif //COMPUTERGRAPHICS_RAY_H
