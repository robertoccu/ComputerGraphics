/**
 * Main function
 */

#include <iostream>
#include "maths/Matrix.h"
#include "geometry/ray.h"

using namespace std;

int main(){
    ray r(Vector(0,0,0,1), Vector(0,0,1,0));
    cout<<r<<endl;
}

