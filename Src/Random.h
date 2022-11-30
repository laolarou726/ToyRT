//
// Created by luoli on 2022/11/29.
//

#ifndef COMPUTERGRAPHICS_RANDOM_H
#define COMPUTERGRAPHICS_RANDOM_H

#include <random>

class Random {
private:
    static std::random_device rd;
    static std::mt19937 mt;
    static std::uniform_real_distribution<double> dist;
public:
    static double next();
    static double next(double max);
    static double next(double min, double max);

    static int nextInt();
    static int nextInt(int max);
    static int nextInt(int min, int max);
};

#endif //COMPUTERGRAPHICS_RANDOM_H
