//
// Created by luoli on 2022/9/6.
//

#ifndef COMPUTERGRAPHICS_TUPLE_H
#define COMPUTERGRAPHICS_TUPLE_H

#include "iostream"
#include "Random.h"
#include <random>
#include <climits>

using namespace std;

class Tuple {
public:
    double x, y, z, w;

    // Default constructor - initializes Tuple to be a vector having coordinate
    // values (x 0, y 0, z 0, w 0)
    Tuple();

    // Vector constructor - initializes Tuple to be a vector having coordinate
    // values x, y, and z as given. The w value will be automatically set to 0.
    Tuple(double x, double y, double z);

    // Point constructor - initializes Tuple to be a point having coordinate
    // values x, y, and z as given. The fourth argument is expected to be any
    // positive value, but will always be stored as w = 1.0
    // The C++ compiler will call this version when it sees four type double arguments.
    Tuple(double x, double y, double z, double w);

    // Copy constructor - receives another Tuple as argument.
    // Initialize this Tuple to hold identical x, y, z, and w values as the given argument Tuple.
    Tuple(const Tuple &source);

    // Return true if this Tuple is a vector (has w value of zero)
    // Hint: Use the absolute value function check for zero.
    // If the absolute value of w is less than 0.001 (or similar small epsilon value), then we
    // assume that the w value is "equal" to zero.
    // When using float or double the == can often report false when the two
    // values are close enough to being equal.
    // https://cplusplus.com/reference/cmath/abs/
    [[nodiscard]] bool isVector() const;

    // Return true if this Tuple is a point (has w value > 0)
    [[nodiscard]] bool isPoint() const;

    // Increments this x, y, z, and w by respective values from otherTuple.
    // If this tuple and otherTuple are both points whose w values are 1, then
    // the addition will leave this->w at 2.0. If we find this->w > 1, then set this->w = 1.
    void add(const Tuple &otherTuple);

    // Decrements this x, y, z, and w by respective values from otherTuple.
    // If this tuple is a vector and otherTuple a point whose w values are 1, then
    // the subtraction will leave this->w at -1. If we find this->w < -0.5, then set this->w = 1
    // so that the result is a point.
    void sub(const Tuple &otherTuple);

    // Multiplies x, y, and z values of this Tuple by the given scalar value S.
    // Tuple's w value is not changed.
    void multScalar(double S);

    // Return the length or magnitude of this point or vector.
    // If Tuple is a point, then length is the distance of this point from the origin point (0,0,0).
    // If Tuple is a vector, then length is the magnitude of the vector.
    // The Tuple's w value does not contribute to its length.
    double magnitude() const;

    // Change this vector to unit-length.
    // A unit-length vector is one whose length or magnitude is 1.0.
    // pre-condition: This Tuple must be a vector. If is a point, then do nothing.
    // First, find the magnitude of this vector.
    // Second, if the magnitude is > 0, then divide this Tuple's
    // x, y, and z values by the magnitude.
    // Do not divide when the magnitude is 0 since this will cause a divide by zero crash.
    // Normalize does not change the Tuple's w value.
    void normalize();

    // Return the dot product of two vectors.
    // pre-condition: this Tuple and otherTuple must both be vectors.
    // returns dot product of this Tuple and otherTuple using only their x, y, and z values.
    // Otherwise, return 0 if this Tuple and otherTuple are not both vectors.
    [[nodiscard]] double dot(const Tuple &otherTuple) const;
    [[nodiscard]] Tuple vectorDot(const Tuple &otherTuple) const;
    [[nodiscard]] Tuple cross(const Tuple &otherTuple) const;

    // Print formatted display of Tuple to std::cout.
    // Example print out: (1, 2, 3, 0) for a vector.
    // Print the values in order of x, y, z, and w.
    void print() const;

    // Overloaded operators. The class declares these functions as its 'friends.'
    // The implementation code for the friend functions will receive Tuple object arguments.
    // The friend functions will be able to access the private data attributes
    // by saying name_of_tuple_argument.x, etc.
    // We will not prefix friend implemenations with Tuple:: since they are not
    // class member functions.

    // Reference: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend ostream &operator<<(ostream &os, const Tuple &T);

    friend Tuple operator/(const Tuple &a, double val);

    //--- Allows us to write A + B to compute the Tuple that results from calling A.add(B)
    //--- Code-reuse tip - Call on your add method
    friend Tuple operator+(const Tuple &a, const Tuple &b);

    //--- Allows us to write A - B to compute the Tuple that results from calling A.sub(B)
    //--- Code-reuse tip - Call on your sub method
    friend Tuple operator-(const Tuple &a, const Tuple &b);

    //--- Allows us to write A * 1.5 to compute the Tuple that results from calling A.multScalar(1.5)
    //--- Code-reuse tip - Call on your multScalar method
    friend Tuple operator*(const Tuple &a, double s);

    //--- Allows us to write 1.5 * A to compute the Tuple that results from calling A.multScalar(1.5)
    //--- Code-reuse tip - Call on your multScalar method
    friend Tuple operator*(double s, const Tuple &a);

    friend bool operator==(const Tuple &a, const Tuple &b);
    friend bool operator!=(const Tuple &a, const Tuple &b);

    static Tuple unitX(){
        return {1, 0, 0};
    }

    static Tuple unitY(){
        return {0, 1, 0};
    }

    static Tuple unitZ(){
        return {0, 0, 1};
    }

    static Tuple zero(){
        return {0, 0, 0};
    }

    static Tuple one(){
        return {1, 1, 1};
    }

    static Tuple INF(){
        return {INT_MIN, INT_MIN, INT_MIN};
    }

    static Tuple RAND(){
        return {
                Random::next() - 0.5,
                Random::next() - 0.5,
                Random::next() - 0.5
        };
    }

    static Tuple RAND_NORM(){
        Tuple result = RAND();
        result.normalize();

        return result;
    }

    static Tuple reduceToMax(const Tuple &vector, const Tuple &limit){
        auto result = Tuple(vector);

        if (result.x > limit.x) result.x = limit.x;
        if (result.y > limit.y) result.y = limit.y;
        if (result.z > limit.z) result.z = limit.z;

        return result;
    }
};


#endif //COMPUTERGRAPHICS_TUPLE_H
