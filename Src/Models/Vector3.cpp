//
// Created by luoli on 2022/9/6.
//

#include "Vector3.h"
#include <cmath>

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;

    w = 0;
}

Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;

    w = 0;
}

Vector3::Vector3(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;

    this->w = w;
}

Vector3::Vector3(const Vector3 &source) {
    x = source.x;
    y = source.y;
    z = source.z;

    w = source.w;
}

bool Vector3::isVector() const {
    return abs(w) < 0.001;
}

bool Vector3::isPoint() const {
    return abs(w) >= 0.001;
}

void Vector3::add(const Vector3 &otherTuple) {
    x += otherTuple.x;
    y += otherTuple.y;
    z += otherTuple.z;

    w += otherTuple.w;

    if(w > 1)
        w = 1;
}

void Vector3::sub(const Vector3 &otherTuple) {
    x -= otherTuple.x;
    y -= otherTuple.y;
    z -= otherTuple.z;

    w -= otherTuple.w;

    if(w < -0.5)
        w = 1;
}

void Vector3::multScalar(double S) {
    x *= S;
    y *= S;
    z *= S;
}

double Vector3::magnitude() const {
    return isVector()
    ? sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))
    : 0;
}

void Vector3::normalize() {
    if(isPoint()) return;

    auto mag = magnitude();

    if(mag > 0){
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

double Vector3::dot(const Vector3 &otherTuple) const {
    if(!isVector() || !otherTuple.isVector()) return 0;

    return x * otherTuple.x +
            y * otherTuple.y +
            z * otherTuple.z;
}

void Vector3::print() const {
    cout << "(" << x << ", " << y << ", " << z << ")" << endl;
}

ostream &operator<<(ostream &os, const Vector3 &T) {
    os << "(" << T.x << ", " << T.y << ", " << T.z << ", " << T.w << ")" << endl;

    return os;
}

Vector3 operator+(const Vector3 &a, const Vector3 &b) {
    auto result = Vector3(a);

    result.add(b);

    return result;
}

Vector3 operator-(const Vector3 &a, const Vector3 &b) {
    auto result = Vector3(a);

    result.sub(b);

    return result;
}

Vector3 operator*(const Vector3 &a, double s) {
    auto result = Vector3(a);

    result.multScalar(s);

    return result;
}

Vector3 operator*(double s, const Vector3 &a) {
    auto result = Vector3(a);

    result.multScalar(s);

    return result;
}

bool operator==(const Vector3 &a, const Vector3 &b) {
    return a.x == b.x &&
            a.y == b.y &&
            a.z == b.z &&
            a.w == b.w;
}

bool operator!=(const Vector3 &a, const Vector3 &b) {
    return !(a == b);
}

Vector3 Vector3::cross(const Vector3 &otherTuple) const {
    return {
        y * otherTuple.z - z * otherTuple.y,
        -(x * otherTuple.z - z * otherTuple.x),
        x * otherTuple.y - y * otherTuple.x
    };
}

Vector3 Vector3::vectorDot(const Vector3 &otherTuple) const {
    return {
        x * otherTuple.x,
        y * otherTuple.y,
        z * otherTuple.z
    };
}

Vector3 operator/(const Vector3 &a, double val) {
    auto result = Vector3(a);
    result.multScalar(1.0 / val);

    return result;
}
