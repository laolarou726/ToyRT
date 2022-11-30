//
// Created by luoli on 2022/9/16.
//

#ifndef COMPUTERGRAPHICS_RAY_H
#define COMPUTERGRAPHICS_RAY_H


#include "../Tuple.h"
#include "../Scene.h"

class Ray {
private:
    int maxBounces;
public:
    Tuple origin;
    Tuple direction;

    explicit Ray(const Tuple &direction, int maxBounces = 4);
    explicit Ray(const Tuple &origin, const Tuple &direction, int maxBounces = 4);
    virtual Tuple emit(const Scene &scene);
};


#endif //COMPUTERGRAPHICS_RAY_H
