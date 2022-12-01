//
// Created by luoli on 2022/9/6.
//

#ifndef COMPUTERGRAPHICS_TUPLE_H
#define COMPUTERGRAPHICS_TUPLE_H

#include "iostream"
#include "../Utils/Random.h"
#include <random>
#include <climits>

using namespace std;

class Vector3 {
public:
    double x, y, z, w;

    // Default constructor - initializes Vector3 to be a vector having coordinate
    // values (x 0, y 0, z 0, w 0)
    Vector3();

    // Vector constructor - initializes Vector3 to be a vector having coordinate
    // values x, y, and z as given. The w value will be automatically set to 0.
    Vector3(double x, double y, double z);

    // Point constructor - initializes Vector3 to be a point having coordinate
    // values x, y, and z as given. The fourth argument is expected to be any
    // positive value, but will always be stored as w = 1.0
    // The C++ compiler will call this version when it sees four type double arguments.
    Vector3(double x, double y, double z, double w);

    // Copy constructor - receives another Vector3 as argument.
    // Initialize this Vector3 to hold identical x, y, z, and w values as the given argument Vector3.
    Vector3(const Vector3 &source);

    // Return true if this Vector3 is a vector (has w value of zero)
    // Hint: Use the absolute value function check for zero.
    // If the absolute value of w is less than 0.001 (or similar small epsilon value), then we
    // assume that the w value is "equal" to zero.
    // When using float or double the == can often report false when the two
    // values are close enough to being equal.
    // https://cplusplus.com/reference/cmath/abs/
    [[nodiscard]] bool isVector() const;

    // Return true if this Vector3 is a point (has w value > 0)
    [[nodiscard]] bool isPoint() const;

    // Increments this x, y, z, and w by respective values from otherTuple.
    // If this tuple and otherTuple are both points whose w values are 1, then
    // the addition will leave this->w at 2.0. If we find this->w > 1, then set this->w = 1.
    void add(const Vector3 &otherTuple);

    // Decrements this x, y, z, and w by respective values from otherTuple.
    // If this tuple is a vector and otherTuple a point whose w values are 1, then
    // the subtraction will leave this->w at -1. If we find this->w < -0.5, then set this->w = 1
    // so that the result is a point.
    void sub(const Vector3 &otherTuple);

    // Multiplies x, y, and z values of this Vector3 by the given scalar value S.
    // Vector3's w value is not changed.
    void multScalar(double S);

    // Return the length or magnitude of this point or vector.
    // If Vector3 is a point, then length is the distance of this point from the origin point (0,0,0).
    // If Vector3 is a vector, then length is the magnitude of the vector.
    // The Vector3's w value does not contribute to its length.
    double magnitude() const;

    // Change this vector to unit-length.
    // A unit-length vector is one whose length or magnitude is 1.0.
    // pre-condition: This Vector3 must be a vector. If is a point, then do nothing.
    // First, find the magnitude of this vector.
    // Second, if the magnitude is > 0, then divide this Vector3's
    // x, y, and z values by the magnitude.
    // Do not divide when the magnitude is 0 since this will cause a divide by zero crash.
    // Normalize does not change the Vector3's w value.
    void normalize();

    // Return the dot product of two vectors.
    // pre-condition: this Vector3 and otherTuple must both be vectors.
    // returns dot product of this Vector3 and otherTuple using only their x, y, and z values.
    // Otherwise, return 0 if this Vector3 and otherTuple are not both vectors.
    [[nodiscard]] double dot(const Vector3 &otherTuple) const;
    [[nodiscard]] Vector3 vectorDot(const Vector3 &otherTuple) const;
    [[nodiscard]] Vector3 cross(const Vector3 &otherTuple) const;

    // Print formatted display of Vector3 to std::cout.
    // Example print out: (1, 2, 3, 0) for a vector.
    // Print the values in order of x, y, z, and w.
    void print() const;

    // Overloaded operators. The class declares these functions as its 'friends.'
    // The implementation code for the friend functions will receive Vector3 object arguments.
    // The friend functions will be able to access the private data attributes
    // by saying name_of_tuple_argument.x, etc.
    // We will not prefix friend implemenations with Vector3:: since they are not
    // class member functions.

    // Reference: https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-170
    friend ostream &operator<<(ostream &os, const Vector3 &T);

    friend Vector3 operator/(const Vector3 &a, double val);

    //--- Allows us to write A + B to compute the Vector3 that results from calling A.add(B)
    //--- Code-reuse tip - Call on your add method
    friend Vector3 operator+(const Vector3 &a, const Vector3 &b);

    //--- Allows us to write A - B to compute the Vector3 that results from calling A.sub(B)
    //--- Code-reuse tip - Call on your sub method
    friend Vector3 operator-(const Vector3 &a, const Vector3 &b);

    //--- Allows us to write A * 1.5 to compute the Vector3 that results from calling A.multScalar(1.5)
    //--- Code-reuse tip - Call on your multScalar method
    friend Vector3 operator*(const Vector3 &a, double s);

    //--- Allows us to write 1.5 * A to compute the Vector3 that results from calling A.multScalar(1.5)
    //--- Code-reuse tip - Call on your multScalar method
    friend Vector3 operator*(double s, const Vector3 &a);

    friend bool operator==(const Vector3 &a, const Vector3 &b);
    friend bool operator!=(const Vector3 &a, const Vector3 &b);

    static Vector3 unitX(){
        return {1, 0, 0};
    }

    static Vector3 unitY(){
        return {0, 1, 0};
    }

    static Vector3 unitZ(){
        return {0, 0, 1};
    }

    static Vector3 zero(){
        return {0, 0, 0};
    }

    static Vector3 one(){
        return {1, 1, 1};
    }

    static Vector3 INF(){
        return {INT_MIN, INT_MIN, INT_MIN};
    }

    static Vector3 RAND(){
        return {
                Random::next() - 0.5,
                Random::next() - 0.5,
                Random::next() - 0.5
        };
    }

    static Vector3 RAND_NORM(){
        Vector3 result = RAND();
        result.normalize();

        return result;
    }

    static Vector3 reduceToMax(const Vector3 &vector, const Vector3 &limit){
        auto result = Vector3(vector);

        if (result.x > limit.x) result.x = limit.x;
        if (result.y > limit.y) result.y = limit.y;
        if (result.z > limit.z) result.z = limit.z;

        return result;
    }
};


#endif //COMPUTERGRAPHICS_TUPLE_H
