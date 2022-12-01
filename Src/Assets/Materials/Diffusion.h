//
// Created by luoli on 2022/9/25.
//

#ifndef COMPUTERGRAPHICS_DIFFUSION_H
#define COMPUTERGRAPHICS_DIFFUSION_H


#include "../../Models/Vector3.h"
#include "MaterialBase.h"

class Diffusion : public MaterialBase{
public:
    explicit Diffusion(const Vector3 &reflectance);
    static Diffusion* DEFAULT(){
        return new Diffusion({1, 1, 1});
    }
    Vector3 getOutRayDirection(const Vector3 &inRay, const Vector3 &meshNormal) override;
};


#endif //COMPUTERGRAPHICS_DIFFUSION_H
