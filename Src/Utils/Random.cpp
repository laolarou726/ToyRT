//
// Created by luoli on 2022/11/30.
//

#include "Random.h"
#include <climits>

std::random_device Random::rd;
std::mt19937 Random::mt = std::mt19937(rd());
std::uniform_real_distribution<double> Random::dist;

double Random::next() {
    return dist(mt);
}

double Random::next(double max) {
    return next(0, max);
}

double Random::next(double min, double max) {
    return min + (dist(mt) * (max-min+1));
}

int Random::nextInt() {
    return nextInt(INT_MIN, INT_MAX);
}

int Random::nextInt(int max) {
    return nextInt(0, max);
}

int Random::nextInt(int min, int max) {
    return min + (int)(dist(mt) * (max-min+1));
}
