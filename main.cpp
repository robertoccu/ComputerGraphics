/**
 * Main function
 */

#include <iostream>
#include "maths/Matrix.h"
#include "maths/Vector.h"
using namespace std;

int main(){
    Vector v(5,0,0,5);
    Matrix m = Matrix::traslation(0,0,0);
    cout<<v<<endl;
    cout<<m*v<<endl;
}

