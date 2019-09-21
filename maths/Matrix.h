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
    double matrix[4][4];
public:
    Matrix();
    ~Matrix();

    /** Operators **/
    Matrix operator=(const Matrix &m);
    bool isIdentity();

    /** Getter and setter operations */
    double get(int row, int column) const {return matrix[row][column];}
    void set(int row, int column, double value){matrix[row][column] = value;}

    void setPoint(double x, double y, double z);
    Vector getPoint() const;
    void setVector(double x, double y, double z, int positionVector);
    void setVector(Vector &v, int positionVector);
    Vector getVector(int positionVector) const;
    void setScale(double sx, double sy, double sz);
    void setRotX(double x);
    void setRotY(double y);
    void setRotZ(double z);

    /** Return types of matrices **/
    Matrix transpose() const;
    Matrix adjugate() const;
    Matrix inverse() const;
    double determinant() const;

    /** Definition of special matrices **/
    static Matrix traslation(double x, double y, double z);
    static Matrix scale(double sx, double sy, double sz);
    static Matrix rotationXYZ(double x, double y, double z);
    static double determinant3x3(double a11, double a12, double a13,
                                 double a21, double a22, double a23,
                                 double a31, double a32, double a33);

    /** Operator overloading **/
    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(double m) const;
    Matrix operator*(const Matrix &m) const;
    Vector operator*(const Vector &pd) const;

    Matrix operator+=(const Matrix &m);
    Matrix operator-=(const Matrix &m);
    Matrix operator*=(double m);
    Matrix operator*=(const Matrix &m);

    /** Output screen **/
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m);

    /** Comparison operator **/
    bool operator==(const Matrix &rhs) const;
    bool operator!=(const Matrix &rhs) const;
};


#endif //MATRIX_H
