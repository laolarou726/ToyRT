//
// Created by luoli on 2022/9/25.
//

#ifndef COMPUTERGRAPHICS_DIFFUSION_H
#define COMPUTERGRAPHICS_DIFFUSION_H


#include "../../Tuple.h"
#include "MaterialBase.h"

class Diffusion : public MaterialBase{
public:
    explicit Diffusion(const Tuple &reflectance);
    static Diffusion* DEFAULT(){
        return new Diffusion({1, 1, 1});
    }
    Tuple getOutRayDirection(const Tuple &inRay, const Tuple &meshNormal) override;
};


#endif //COMPUTERGRAPHICS_DIFFUSION_H
