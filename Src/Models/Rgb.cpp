//
// Created by luoli on 2022/10/19.
//

#include "Rgb.h"

// Default constructor - initializes r, g, b values to all 0.0
Rgb::Rgb() {
    this->r = this->g = this->b = 0.0;
}

// Initializing constructor - initializes Rgb to have given values.
// Clamps given values so that they each range between 0.0 to 1.0, inclusive.
Rgb::Rgb(double r, double g, double b) {
    // Assign give argument values...
    this->r = r;
    this->g = g;
    this->b = b;
    // Clamp updated r, g, b data member variables to valid range.
    this->clamp();
}

// Copy constructor - receives another Rgb as argument.
// Initialize this Rgb to hold identical r, g, and b values as the given argument.
Rgb::Rgb(const Rgb& src) {
    this->r = src.r;
    this->g = src.g;
    this->b = src.b;
}

// Clamps r, g, b values so they are all between 0.0 and 1.0, inclusive.
void Rgb::clamp() {
    if(this->r < 0.0)
        this->r = 0.0;
    if(this->r > 1.0)
        this->r = 1.0;

    if(this->g < 0.0)
        this->g = 0.0;
    if(this->g > 1.0)
        this->g = 1.0;

    if(this->b < 0.0)
        this->b = 0.0;
    if(this->b > 1.0)
        this->b = 1.0;
}

void Rgb::add( const Rgb& src ) {
    this->r = this->r + src.r;
    this->g = this->g + src.g;
    this->b = this->b + src.b;
    this->clamp();
}

void Rgb::multScalar(double s) {
    this->r = this->r * s;
    this->g = this->g * s;
    this->b = this->b * s;
    this->clamp();
}

void Rgb::mult(const Rgb& src) {
    this->r = this->r * src.r;
    this->g = this->g * src.g;
    this->b = this->b * src.b;
    this->clamp();
}

double Rgb::getR() const {
    return this->r;
}

double Rgb::getG() const {
    return this->g;
}

double Rgb::getB() const {
    return this->b;
}

// Reference: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
ostream& operator<<(ostream& os, const Rgb& T) {
    os << "(" << T.r << ", " << T.g << ", " << T.b << ")";
    return os;
}

Rgb operator+(const Rgb& a, const Rgb& b) {
    Rgb result(a);
    result.add(b);
    return result;
}

Rgb operator*(const Rgb& a, double s) {
    Rgb result(a);
    result.multScalar(s);
    return result;
}

Rgb operator*(double s, const Rgb& a) {
    Rgb result(a);
    result.multScalar(s);
    return result;
}

Rgb operator*(const Rgb& a, const Rgb& b) {
    Rgb result(a);
    result.mult(b);
    return result;
}
