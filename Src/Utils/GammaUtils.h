//
// Created by luoli on 2022/12/8.
//

#ifndef TOYRT_GAMMAUTILS_H
#define TOYRT_GAMMAUTILS_H


#include <unordered_map>
#include "../Models/Vector3.h"

class GammaUtils {
private:
    double factor;
    std::vector<unsigned char> preComputeTable{};
public:
    explicit GammaUtils(double factor = 2.2);
    Vector3 correct(const Vector3 &input);
};


#endif //TOYRT_GAMMAUTILS_H
