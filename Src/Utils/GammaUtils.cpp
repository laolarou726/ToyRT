//
// Created by luoli on 2022/12/8.
//

#include "GammaUtils.h"
#include "fmt/format.h"

GammaUtils::GammaUtils(double factor) {
    this->factor = factor;

    for (int i = 0; i < 256; i++) {
        double f = (double)i / 255.0;
        f = pow(f, 1.0 / this->factor);

        this->preComputeTable.emplace_back((int)(f * 255.0));
    }
}

Vector3 GammaUtils::correct(const Vector3 &input) {
    Vector3 ceilInput = input;
    ceilInput.x = ceil(ceilInput.x);
    ceilInput.y = ceil(ceilInput.y);
    ceilInput.z = ceil(ceilInput.z);

    return {
        (double)this->preComputeTable[(char)ceilInput.x],
        (double)this->preComputeTable[(char)ceilInput.y],
        (double)this->preComputeTable[(char)ceilInput.z]
    };
}
