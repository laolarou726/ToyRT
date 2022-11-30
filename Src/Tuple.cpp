//
// Created by luoli on 2022/9/6.
//

#include "Tuple.h"
#include <cmath>

Tuple::Tuple() {
    x = 0;
    y = 0;
    z = 0;

    w = 0;
}

Tuple::Tuple(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;

    w = 0;
}

Tuple::Tuple(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;

    this->w = w;
}

Tuple::Tuple(const Tuple &source) {
    x = source.x;
    y = source.y;
    z = source.z;

    w = source.w;
}

bool Tuple::isVector() const {
    return abs(w) < 0.001;
}

bool Tuple::isPoint() const {
    return abs(w) >= 0.001;
}

void Tuple::add(const Tuple &otherTuple) {
    x += otherTuple.x;
    y += otherTuple.y;
    z += otherTuple.z;

    w += otherTuple.w;

    if(w > 1)
        w = 1;
}

void Tuple::sub(const Tuple &otherTuple) {
    x -= otherTuple.x;
    y -= otherTuple.y;
    z -= otherTuple.z;

    w -= otherTuple.w;

    if(w < -0.5)
        w = 1;
}

void Tuple::multScalar(double S) {
    x *= S;
    y *= S;
    z *= S;
}

double Tuple::magnitude() const {
    return isVector()
    ? sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))
    : 0;
}

void Tuple::normalize() {
    if(isPoint()) return;

    auto mag = magnitude();

    if(mag > 0){
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

double Tuple::dot(const Tuple &otherTuple) const {
    if(!isVector() || !otherTuple.isVector()) return 0;

    return x * otherTuple.x +
            y * otherTuple.y +
            z * otherTuple.z;
}

void Tuple::print() const {
    cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

ostream &operator<<(ostream &os, const Tuple &T) {
    os << "(" << T.x << ", " << T.y << ", " << T.z << ", " << T.w << ")" << endl;

    return os;
}

Tuple operator+(const Tuple &a, const Tuple &b) {
    auto result = Tuple(a);

    result.add(b);

    return result;
}

Tuple operator-(const Tuple &a, const Tuple &b) {
    auto result = Tuple(a);

    result.sub(b);

    return result;
}

Tuple operator*(const Tuple &a, double s) {
    auto result = Tuple(a);

    result.multScalar(s);

    return result;
}

Tuple operator*(double s, const Tuple &a) {
    auto result = Tuple(a);

    result.multScalar(s);

    return result;
}

bool operator==(const Tuple &a, const Tuple &b) {
    return a.x == b.x &&
            a.y == b.y &&
            a.z == b.z &&
            a.w == b.w;
}

bool operator!=(const Tuple &a, const Tuple &b) {
    return !(a == b);
}

Tuple Tuple::cross(const Tuple &otherTuple) const {
    return {
        y * otherTuple.z - z * otherTuple.y,
        -(x * otherTuple.z - z * otherTuple.x),
        x * otherTuple.y - y * otherTuple.x
    };
}

Tuple Tuple::vectorDot(const Tuple &otherTuple) const {
    return {
        x * otherTuple.x,
        y * otherTuple.y,
        z * otherTuple.z
    };
}

Tuple operator/(const Tuple &a, double val) {
    auto result = Tuple(a);
    result.multScalar(1.0 / val);

    return result;
}