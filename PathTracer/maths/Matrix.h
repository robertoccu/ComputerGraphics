/**
 * The matrix class represents any matrix of 4 rows by 4 columns, i.e. 4x4.
 * It can be a translational, scalar, rotational or base change matrix.
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "Vector.h"

class Matrix {
private:
    float matrix[4][4];
public:
    Matrix();
    ~Matrix();

    /** Operators **/
    Matrix operator=(const Matrix &m);
    bool isIdentity();

    /** Getter and setter operations */
    float get(int row, int column) const {return matrix[row][column];}
    void set(int row, int column, float value){matrix[row][column] = value;}

    void setPoint(float x, float y, float z);
    void setPoint(const Vector &p);
    Vector getPoint() const;
    void setVector(float x, float y, float z, int positionVector);
    void setVector(const Vector &v, int positionVector);
    void setVectors(const Vector &x, const Vector &y, const Vector &z);
    Vector getVector(int positionVector) const;
    void setScale(float sx, float sy, float sz);
    void setRotX(float x);
    void setRotY(float y);
    void setRotZ(float z);

    /** Return types of matrices **/
    Matrix transpose() const;
    Matrix adjugate() const;
    Matrix inverse() const;
    float determinant() const;

    /** Definition of special matrices **/
    static Matrix traslation(float x, float y, float z);
    static Matrix scale(float sx, float sy, float sz);
    static Matrix rotationXYZ(float x, float y, float z);
    static float determinant3x3(float a11, float a12, float a13,
                                 float a21, float a22, float a23,
                                 float a31, float a32, float a33);

    /** Operator overloading **/
    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(float m) const;
    Matrix operator*(const Matrix &m) const;
    Vector operator*(const Vector &pd) const;

    Matrix operator+=(const Matrix &m);
    Matrix operator-=(const Matrix &m);
    Matrix operator*=(float m);
    Matrix operator*=(const Matrix &m);

    /** Output screen **/
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

    /** Comparison operator **/
    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;
};


#endif //MATRIX_H
