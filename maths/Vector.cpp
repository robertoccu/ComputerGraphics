/**
 * The Vector class represents a vector in 3D space with a homogeneous coordinate.
 * It contains all possible operations that can be done to a vector.
 */

#include <cmath>
#include <iomanip>
#include "Vector.h"

/**
 * Default constructor
 */
Vector::Vector(){
    vector[0] = 0.0;
    vector[1] = 0.0;
    vector[2] = 0.0;
    vector[3] = 0.0;
}

/**
 * Parameterized constructor
 * @param x coordinate
 * @param y coordinate
 * @param z coordinate
 * @param homogeneousCoordinate
 */
Vector::Vector(float x, float y, float z, int homogeneousCoordinate){
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = (float)homogeneousCoordinate;
}

// Default destructor
Vector::~Vector(){}

 /**
  * Operator assignment
  * @param v1 vector to copy
  * @return
  */
Vector& Vector::operator=(const Vector &v1){
    vector[0] = v1.get(0);
    vector[1] = v1.get(1);
    vector[2] = v1.get(2);
    vector[3] = v1.get(3);
    return *this;
}

/* Setter and getter operations */

/**
 * Return the value of the position
 * @param position
 * @return float
 */
float Vector::get(int position) const{
    return vector[position];
}

/**
 * Set the value in the position
 * @param position  position where write
 * @param value value to write
 */
void Vector::set(int position, float value){
    vector[position] = value;
}

/* Setter on points and directions */

/**
 * Set the point defined by x,y and z. A point is defined by a homogeneneus coordinate to 1
 * @param x coordinate x
 * @param y coordinate y
 * @param z coordinate z
 */
void Vector::setPoint(float x, float y, float z){
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = 1;
}

/**
 * Set the direction defined by x, y and z. A direction is defined by a homogeneous coordinate to 0.
 * @param x coordinate x
 * @param y coordinate y
 * @param z coordinate z
 */
void Vector::setDirection(float x, float y, float z){
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    vector[3] = 0;
}

/** Vector operations **/

/**
 * Returns the module of the vector, i.e. the square root of the sum of the components squared.
 * @return modulus of the vector
 */
float Vector::modulus() const{
    float modulus = 0.0;
    for(int i = 0; i < 3; i++){
        modulus += this->get(i) * this->get(i);
    }
    return sqrtl(modulus);
}

/**
 * Returns the normalized vector, that is, with module 1
 * @return Vector normalized
 */
Vector Vector::normalize() const{
    return *this/this->modulus();
}

/**
 * Returns the negated vector, that is, its components changed from sign
 * @return Vector negate
 */
Vector Vector::negate() const{
    return *this*(-1.0);
}

/**
 * Returns a vector perpendicular to the vector. A vector is perpendicular if its dot product is 0
 * @return Perpendicular vector
 */
Vector Vector::perpendicular() const{
    Vector perpendicular;
    if(fabs(this->get(0)) > fabs(this->get(1))){
        perpendicular = Vector(this->get(2), 0, this->get(0), 0);
    }else{
        perpendicular = Vector(0, -this->get(2), this->get(1), 0);
    }

    return perpendicular;
}

/* Operator overload */

/**
 * Returns the sum of two vectors
 * @param v1 second operator
 * @return Vector sum
 */
Vector Vector::operator+(const Vector &v1) const{
    Vector sum;
    for(int i = 0; i < 4; i++){
        sum.set(i, this->get(i) + v1.get(i));
    }
    return sum;
}

/**
 * Returns the subtraction of two vectors
 * @param v1 second operator
 * @return Vector sub
 */
Vector Vector::operator-(const Vector &v1) const{
    Vector sub;
    for(int i = 0; i < 4; i++){
        sub.set(i, this->get(i) - v1.get(i));
    }
    return sub;
}

/**
 * Return de cross product of two vectors
 * @param v1
 * @param v2
 * @return cross product vector
 */
Vector Vector::cross(const Vector &v1, const Vector &v2){
    Vector vectorReturned;
    vectorReturned.set(0, (v1.get(1)*v2.get(2) -
                                    v1.get(2)*v2.get(1)) );
    vectorReturned.set(1, (v1.get(2)*v2.get(0) -
                                    v1.get(0)*v2.get(2)) );
    vectorReturned.set(2, (v1.get(0)*v2.get(1) -
                                    v1.get(1)*v2.get(0)) );
    vectorReturned.set(3, 0);

    return vectorReturned;
}

/**
 * Dot product of two vectors
 * @param v1
 * @param v2
 * @return
 */
float Vector::dot(const Vector &v1, const Vector &v2){
    float dot = 0.0;
    for(int i = 0; i < 4; i++){
        dot += v1.get(i) * v2.get(i);
    }
    return dot;
}

/**
 * Return the dot product
 * @param v1
 * @return dot product float
 */
Vector Vector::operator*(const Vector &v1) const{
    Vector new_vector;
    for(int i = 0; i < 4; i++){
        new_vector.set(i, this->get(i) * v1.get(i));
    }
    return new_vector;
}

/**
 * Return the vector multiplied by a scalar
 * @param scalar
 * @return Vector multiplied
 */
Vector Vector::operator*(float scalar) const{
    Vector multiplied;
    multiplied.set(0, this->get(0) * scalar);
    multiplied.set(1, this->get(1) * scalar);
    multiplied.set(2, this->get(2) * scalar);
    return multiplied;
}

/**
 * The same operation but with the inverse order
 * @param scalar
 * @param v1
 * @return Vector multiplied
 */
Vector operator*(float scalar, const Vector &v1){
    return v1 * scalar;
}

/**
 * Return the vector divide by a scalar
 * @param scalar
 * @return Vector divided
 * @throw Error if scalar is 0
 */
Vector Vector::operator/(float scalar) const{
    if(scalar == 0){
        std::string message = "ERROR Vector::operator/: division to 0 !";
        throw std::out_of_range(message);
    }
    Vector divided;
    divided.set(0, this->get(0) / scalar);
    divided.set(1, this->get(1) / scalar);
    divided.set(2, this->get(2) / scalar);
    return divided;
}

/**
 *
 * @param v1
 * @return
 */
Vector Vector::operator+=(const Vector &v1){
    *this = this->operator+(v1);
    return *this;
}

/**
 *
 * @param v1
 * @return
 */
Vector Vector::operator-=(const Vector &v1){
    *this = this->operator-(v1);
    return *this;
}

/**
 *
 * @param scalar
 * @return
 */
Vector Vector::operator*=(float scalar){
    *this = this->operator*(scalar);
    return *this;
}

/**
 *
 * @param scalar
 * @return
 */
Vector Vector::operator/=(float scalar){
    *this = this->operator/(scalar);
    return *this;
}


/* Compare Operators */

/**
 * Return true if the all values are the same in the two vectors.
 * @param v1
 * @return true if equals
 */
bool Vector::operator==(const Vector &v1) const{
    return (this->get(0) == v1.get(0) &&
            this->get(1) == v1.get(1) &&
            this->get(2) == v1.get(2) &&
            this->get(3) == v1.get(3));
}

/**
 * Return true if one of the values are different in the two vectors.
 * @param v1
 * @return true if not equals
 */
bool Vector::operator!=(const Vector &v1) const{
    return !(this->operator==(v1));
}

/**
 * Shows on screen the vector with a defined format. Each component of the vector in a different row
 * @param os
 * @param v1
 * @return the output screen
 */
std::ostream &operator<<(std::ostream &os, const Vector &v1){
    os << std::fixed;
    os << std::setprecision(2);     // Number of decimals

    os << std::setw(7)<<"[x: "<<v1.get(0);
    os << std::setw(7)<<", y: "<<v1.get(1);
    os << std::setw(7)<<", z: "<<v1.get(2);
    os << std::setw(7)<<", h: "<<v1.get(3)<<"]";

    return os;
}

Vector operator/(float scalar, const Vector &v1) {
    return Vector(v1.get(0) / scalar, v1.get(1) / scalar,v1.get(2) / scalar,v1.get(3));
}
