/**
 * The Vector class represents a vector in 3D space with a homogeneous coordinate.
 * It contains all possible operations that can be done to a vector.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

#define VEC 0
#define PT 1

/**
 * vector[0] = X Component
 * vector[1] = Y Component
 * vector[2] = Z Component
 * vector[3] = Homogeneous Coordinate
 */
class Vector {
private:
    float vector[4];
public:
    Vector();   // Default constructor
    Vector(float x, float y, float z, int homogeneousCoordinate);

    ~Vector();  // Default destructor

    /* Operator Assignment */
    Vector& operator=(const Vector &v1);

    /* Setter and getter operations */
    float get(int position) const;
    void set(int position, float value);

    /* Setter on points and directions */
    void setPoint(float x, float y, float z);
    void setDirection(float x, float y, float z);

    /* Boolean Operations */
    bool isPoint() const { return vector[3] == 1; }     // Returns true if the vector is a point
    bool isDirection() const { return vector[3] == 0; } // Returns true if the vector is a direction

    /* Vector operations */
    float modulus() const;         // Returns the vector modulus
    Vector normalize() const;       // Returns the normalized vector, i.e module 1
    Vector negate() const;          // Returns the negated vector
    Vector perpendicular() const;   // Returns a vector perpendicular to the vector

    /* Operator overload */
    Vector operator+(const Vector &v1) const;                           // Sum of two vectors
    Vector operator-(const Vector &v1) const;                           // Subtraction of two vectors
    static Vector cross(const Vector &v1, const Vector &v2);             // Cross product
    static float dot(const Vector &v1, const Vector &v2);
    Vector operator*(const Vector &v1) const;                           // Multiply operation
    // With other types
    Vector operator*(float scalar) const;                              // Vector multiplied by scale
    friend Vector operator*(float scalar, const Vector &v1);           // Distribution operation
    Vector operator/(float scalar) const;                              // Vector divide by scale
    Vector operator+=(const Vector &v1);                                // Vector = Vector + v1
    Vector operator-=(const Vector &v1);                                // Vector = Vector - v1;
    Vector operator*=(float scalar);                                   // Vector = Vector * scalar
    Vector operator/=(float scalar);                                   // Vector = Vector / scalar

    /* Compare Operators */
    bool operator==(const Vector &v1) const;
    bool operator!=(const Vector &v1) const;

    /* Screen output */
    friend std::ostream &operator<<(std::ostream &os, const Vector &v1);

};


#endif //VECTOR_H
