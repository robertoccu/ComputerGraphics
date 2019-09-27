/**
 * The matrix class represents any matrix of 4 rows by 4 columns, i.e. 4x4.
 * It can be a translational, scalar, rotational or base change matrix.
 */

#include <iomanip>
#include <cmath>
#include "Matrix.h"

/**
 * Default constructor. Return the identity matrix, i.e. the matrix whose diagonal is all 1.
 */
Matrix::Matrix(){
    matrix[0][0] = 1.0; matrix[0][1] = 0.0; matrix[0][2] = 0.0; matrix[0][3] = 0.0;
    matrix[1][0] = 0.0; matrix[1][1] = 1.0; matrix[1][2] = 0.0; matrix[1][3] = 0.0;
    matrix[2][0] = 0.0; matrix[2][1] = 0.0; matrix[2][2] = 1.0; matrix[2][3] = 0.0;
    matrix[3][0] = 0.0; matrix[3][1] = 0.0; matrix[3][2] = 0.0; matrix[3][3] = 1.0;
}
/**
 * Default empty destructor
 */
Matrix::~Matrix(){}

/** Operators **/
/**
 * Asignment operator
 * @param m the matrix to copy
 * @return the matrix copied
 */
Matrix Matrix::operator=(const Matrix &m){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            matrix[i][j] = m.get(i, j);
        }
    }

    return *this;
}

/**
 * Return true if the matrix is the identity matrix, whose diagonal is all 1 and the other 0.
 * @return true if the matrix is the identity
 */
bool Matrix::isIdentity(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(i == j){
                // Diagonal case
                if(this->get(i, j) != 1){
                    return false;
                }
            }else{
                // No diagonal case
                if(this->get(i, j) != 0){
                    return false;
                }
            }
        }
    }

    return true;
}

/** Getter and setter operations */

/**
 * Set the point in the matrix. The point is set in the 3th column starting with 0
 * @param x x coordinate
 * @param y y coordinate
 * @param z z coordinate
 */
void Matrix::setPoint(double x, double y, double z){
    this->set(0,3,x);
    this->set(1,3,y);
    this->set(2,3,z);
    this->set(3,3,1);
}

/**
 * Return the point of the matrix. The point is set in the 3th column starting with 0
 * @return the point of the matrix
 */
Vector Matrix::getPoint() const{
    return Vector(this->get(0,3),
                  this->get(1,3),
                  this->get(2,3),
                  this->get(3,3));
}

/**
 * Set the vector in the matrix defined by x,y,z in the positionVector column starting with 0
 * @param x x coordinate
 * @param y y coordinate
 * @param z z coordinate
 * @param positionVector column to set the vector starting with 0
 */
void Matrix::setVector(double x, double y, double z, int positionVector){
    if(positionVector > 3 || positionVector < 0){
        std::string message = "ERROR setVector(Vector v, int positionVector): \n\t The vector position must be [0, 3]. "
                              "The position of the vector is: ";
        message.append(std::to_string(positionVector));
        throw std::out_of_range(message);
    }else{
        this->set(0,positionVector,x);
        this->set(1,positionVector,y);
        this->set(2,positionVector,z);
        this->set(3,positionVector,0);
    }

}

/**
 * Set the vector in the matrix defined by v in the positionVector column starting with 0.
 * @param v vector to set
 * @param positionVector column to set starting with 0
 * @throw Error if the positionVector not in [0, 3]
 */
void Matrix::setVector(Vector &v, int positionVector){
    if(positionVector > 3 || positionVector < 0){
        std::string message = "ERROR setVector(Vector v, int positionVector): \n\t The vector position must be [0, 3]. "
                              "The position of the vector is: ";
        message.append(std::to_string(positionVector));
        throw std::out_of_range(message);
    }else{
        this->set(0,positionVector,v.get(0));
        this->set(0,positionVector,v.get(1));
        this->set(0,positionVector,v.get(2));
        this->set(0,positionVector,0);
    }
}

/**
 * Return the vector positioned in the positionVector column
 * @param positionVector column to get the vector starting with 0
 * @return the vector in positionVector of the matrix
 * @throw Error if the positionVector not in [0, 3]
 */
Vector Matrix::getVector(int positionVector) const{
    if(positionVector > 3 || positionVector < 0){
        std::string message = "ERROR setVector(Vector v, int positionVector): \n\t The vector position must be [0, 3]. "
                              "The position of the vector is: ";
        message.append(std::to_string(positionVector));
        throw std::out_of_range(message);
    }else{
        return Vector(this->get(0, positionVector),
                      this->get(1, positionVector),
                      this->get(2, positionVector),
                      0);
    }
}

/**
 * Sets the scaling matrix
 * @param sx scaling of component x
 * @param sy scaling of component y
 * @param sz scaling of component z
 */
void Matrix::setScale(double sx, double sy, double sz){
    this->set(0, 0, this->get(0,0) * sx);
    this->set(1, 1, this->get(1,1) * sy);
    this->set(2, 2, this->get(2,2) * sz);
}

/**
 * Set the rotation matrix in the X-axis in radians
 * @param x radians to rotate in the X-axis
 */
void Matrix::setRotX(double x){
    matrix[1][1] =  cos(x);
    matrix[1][2] = -sin(x);
    matrix[2][1] =  sin(x);
    matrix[2][2] =  cos(x);
}

/**
 * Set the rotation matrix in the Y-axis in radians
 * @param y radians to rotate in the Y-axis
 */
void Matrix::setRotY(double y){
    matrix[0][0] =  cos(y);
    matrix[0][2] =  sin(y);
    matrix[2][0] = -sin(y);
    matrix[2][2] =  cos(y);
}

/**
 * Set the rotation matrix in the Z-axis in radians
 * @param z radians to rotate in the Z-axis
 */
void Matrix::setRotZ(double z){
    matrix[0][0] =  cos(z);
    matrix[0][1] = -sin(z);
    matrix[1][0] =  sin(z);
    matrix[1][1] =  cos(z);
}

/** Return types of matrices **/

/**
 * Return the matrix transpose, i.e. change the rows by the columns and the columns by rows
 * @return matrix transpose
 */
Matrix Matrix::transpose() const{
    Matrix transpose;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            transpose.set(i, j, (this->get(j,i)));
        }
    }

    return transpose;
}

/**
 * Return the adjugate matrix of the original matrix
 * @return adjugate matrix
 */
Matrix Matrix::adjugate() const{
    double value = 0;
    Matrix adjugate;
    /* First column */
    value = Matrix::determinant3x3(this->get(1,1), this->get(1,2),this->get(1,3),
                                   this->get(2,1), this->get(2,2),this->get(2,3),
                                   this->get(3,1), this->get(3,2),this->get(3,3));
    adjugate.set(0, 0, +value);
    value = Matrix::determinant3x3(this->get(0,1), this->get(0,2),this->get(0,3),
                                   this->get(2,1), this->get(2,2),this->get(2,3),
                                   this->get(3,1), this->get(3,2),this->get(3,3));
    adjugate.set(1, 0, -value);
    value = Matrix::determinant3x3(this->get(0,1), this->get(0,2),this->get(0,3),
                                   this->get(1,1), this->get(1,2),this->get(1,3),
                                   this->get(3,1), this->get(3,2),this->get(3,3));
    adjugate.set(2, 0, +value);
    value = Matrix::determinant3x3(this->get(0,1), this->get(0,2),this->get(0,3),
                                   this->get(1,1), this->get(1,2),this->get(1,3),
                                   this->get(2,1), this->get(2,2),this->get(2,3));
    adjugate.set(3, 0, -value);
    /* Second column */
    value = Matrix::determinant3x3(this->get(1,0), this->get(1,2),this->get(1,3),
                                   this->get(2,0), this->get(2,2),this->get(2,3),
                                   this->get(3,0), this->get(3,2),this->get(3,3));
    adjugate.set(0, 1, -value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,2),this->get(0,3),
                                   this->get(2,0), this->get(2,2),this->get(2,3),
                                   this->get(3,0), this->get(3,2),this->get(3,3));
    adjugate.set(1, 1, +value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,2),this->get(0,3),
                                   this->get(1,0), this->get(1,2),this->get(1,3),
                                   this->get(3,0), this->get(3,2),this->get(3,3));
    adjugate.set(2, 1, -value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,2),this->get(0,3),
                                   this->get(1,0), this->get(1,2),this->get(1,3),
                                   this->get(2,0), this->get(2,2),this->get(2,3));
    adjugate.set(3, 1, +value);
    /* Third column */
    value = Matrix::determinant3x3(this->get(1,0), this->get(1,1),this->get(1,3),
                                   this->get(2,0), this->get(2,1),this->get(2,3),
                                   this->get(3,0), this->get(3,1),this->get(3,3));
    adjugate.set(0, 2, +value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,1),this->get(0,2),
                                   this->get(2,0), this->get(2,1),this->get(2,2),
                                   this->get(3,0), this->get(3,1),this->get(3,2));
    adjugate.set(1, 2, -value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,1),this->get(0,3),
                                   this->get(1,0), this->get(1,1),this->get(1,3),
                                   this->get(3,0), this->get(3,1),this->get(3,3));
    adjugate.set(2, 2, +value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,1),this->get(0,3),
                                   this->get(1,0), this->get(1,1),this->get(1,3),
                                   this->get(2,0), this->get(2,1),this->get(2,3));
    adjugate.set(3, 2, -value);
    /* Fourth column */
    value = Matrix::determinant3x3(this->get(1,0), this->get(1,1),this->get(1,2),
                                   this->get(2,0), this->get(2,1),this->get(2,2),
                                   this->get(3,0), this->get(3,1),this->get(3,2));
    adjugate.set(0, 3, -value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,1),this->get(0,2),
                                   this->get(2,0), this->get(2,1),this->get(2,2),
                                   this->get(3,0), this->get(3,1),this->get(3,2));
    adjugate.set(1, 3, +value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,1),this->get(0,2),
                                   this->get(1,0), this->get(1,1),this->get(1,2),
                                   this->get(3,0), this->get(3,1),this->get(3,2));
    adjugate.set(2, 3, -value);
    value = Matrix::determinant3x3(this->get(0,0), this->get(0,1),this->get(0,2),
                                   this->get(1,0), this->get(1,1),this->get(1,2),
                                   this->get(2,0), this->get(2,1),this->get(2,2));
    adjugate.set(3, 3, +value);

    return adjugate;
}

/**
 * Return the inverse of the matrix, only if the matrix is invertible, i.e determinant != 0
 * @return inverse of matrix
 */
Matrix Matrix::inverse() const{
    Matrix inverse;
    double determinant = this->determinant();
    if(determinant != 0){
        inverse = this->adjugate().transpose() * (1 / determinant);
    }else{
        std::string message = "ERROR matrix.inverse(): Determinant must be != 0 ";
        throw std::out_of_range(message);
    }
    return inverse;
}

/**
 * Return the determinant of the matrix
 * @return the determinant of the matrix
 */
double Matrix::determinant() const{
    double valor = 0;
    valor += this->get(0,0) *
            Matrix::determinant3x3(this->get(1,1), this->get(1,2),this->get(1,3),
                                   this->get(2,1), this->get(2,2),this->get(2,3),
                                   this->get(3,1), this->get(3,2),this->get(3,3));
    valor += -this->get(1,0) *
            Matrix::determinant3x3(this->get(0,1), this->get(0,2),this->get(0,3),
                                   this->get(2,1), this->get(2,2),this->get(2,3),
                                   this->get(3,1), this->get(3,2),this->get(3,3));
    valor += this->get(2,0) *
            Matrix::determinant3x3(this->get(0,1), this->get(0,2),this->get(0,3),
                                   this->get(1,1), this->get(1,2),this->get(1,3),
                                   this->get(3,1), this->get(3,2),this->get(3,3));
    valor += -this->get(3,0) *
            Matrix::determinant3x3(this->get(0,1), this->get(0,2),this->get(0,3),
                                   this->get(1,1), this->get(1,2),this->get(1,3),
                                   this->get(2,1), this->get(2,2),this->get(2,3));

    return valor;
}

/** Definition of special matrices **/

/**
 * Return the matrix that moves to point x,y,z.
 * @param x coordinate x
 * @param y coordinate y
 * @param z coordinate z
 * @return the traslation matrix to point
 */
Matrix Matrix::traslation(double x, double y, double z){
    Matrix m;
    m.setPoint(x,y,z);
    return m;
}

/**
 * Return the scale matrix in the 3-axis
 * @param sx x scaling
 * @param sy y scaling
 * @param sz z scaling
 * @return the scale matrix
 */
Matrix Matrix::scale(double sx, double sy, double sz){
    Matrix m;
    m.setScale(sx,sy,sz);
    return m;
}
/**
 * Return the rotation of the matrix in the 3-axis
 * @param x radians in x-axis
 * @param y radians in y-axis
 * @param z radians in z-axis
 * @return the rotation matrix
 */
Matrix Matrix::rotationXYZ(double x, double y, double z){
    Matrix m;
    m.setRotX(x);
    m.setRotY(y);
    m.setRotZ(z);
    return m;
}

/**
 * Return the determinant of the matrix with 3 rows and 3 columns
 * @param a11
 * @param a12
 * @param a13
 * @param a21
 * @param a22
 * @param a23
 * @param a31
 * @param a32
 * @param a33
 * @return
 */
double Matrix::determinant3x3(double a11, double a12, double a13,
                             double a21, double a22, double a23,
                             double a31, double a32, double a33){
    double value = 0;
    value  = ( (a11 * a22 * a33) + (a12 * a23 * a31) + (a13 * a21 * a32) );
    value += -( (a13 * a22 * a31) + (a12 * a21 * a33) + (a11 * a23 * a32) );

    return value;
}

/** Operator overloading **/
Matrix Matrix::operator+(const Matrix &m) const{
    Matrix matrixAux;
    double value;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            value = this->get(i,j) + m.get(i,j);
            matrixAux.set(i, j, value);
        }

    return matrixAux;
}

Matrix Matrix::operator-(const Matrix &m) const{
    Matrix matrixAux;
    double value;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            value = this->get(i,j) - m.get(i,j);
            matrixAux.set(i, j, value);
        }

    return matrixAux;
}

Matrix Matrix::operator*(double m) const{
    Matrix product;
    double value;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++){
            value = this->get(i,j);
            product.set(i,j,value*m);
        }

    return product;
}

Matrix Matrix::operator*(const Matrix &m) const{
    Matrix product;
    double value = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            for(int k = 0; k < 4; k++){
                value += this->get(i,k) * m.get(k,j);
            }
            product.set(i,j,value);
            value = 0;
        }
    }
    return product;
}

Vector Matrix::operator*(const Vector &pd) const{
    Vector result;
    double value;
    for(int i = 0; i < 4; i++) {
        value = 0;
        for (int j = 0; j < 4; j++) {
            value += (this->get(i, j) * pd.get(j));
        }
        result.set(i, value);
    }

    return result;
}

/**
 *
 * @param m
 * @return
 */
Matrix Matrix::operator+=(const Matrix &m){
    *this = this->operator+(m);
    return *this;
}

/**
 *
 * @param m
 * @return
 */
Matrix Matrix::operator-=(const Matrix &m){
    *this = this->operator-(m);
    return *this;
}

/**
 *
 * @param m
 * @return
 */
Matrix Matrix::operator*=(double m){
    *this = this->operator*(m);
    return *this;
}

/**
 *
 * @param m
 * @return
 */
Matrix Matrix::operator*=(const Matrix &m){
    *this = this->operator*(m);
    return *this;
}

/**
 *
 */
std::ostream &operator<<(std::ostream &os, const Matrix &m){
    os << std::fixed;
    os << std::setprecision(2);
    os<<std::endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            os<<std::setw(7)<<m.get(i,j)<<" ";
        }
        os<<std::endl;
    }

    return os;
}

/**
 * Return true if the all elements are the same
 * @param rhs matrix to compare
 * @return true if the all elements are the same
 */
bool Matrix::operator==(const Matrix &rhs) const {
    return matrix == rhs.matrix;
}

/**
 * Return true if the one element are different
 * @param rhs matrix to compare
 * @return true if the one element are different
 */
bool Matrix::operator!=(const Matrix &rhs) const {
    return !(rhs == *this);
}
