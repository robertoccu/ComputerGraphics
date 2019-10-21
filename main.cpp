/**
 * Main function
 */

#include <iostream>
#include <ctime>
#include "maths/Matrix.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "utils/PlanetaryMaths.h"

using namespace std;

int main(){
    unsigned init_time, finish_time;
    // Obtain the timestamp
    init_time = clock();

    // Run the main program
    cout<<"COMPUTER GRAPHICS"<<endl;
    planetary_main();

    // To finish, obtain the timestamp
    finish_time = clock();
    double time = (double(finish_time - init_time) / CLOCKS_PER_SEC);
    if(time >= 60){ // More or equal to 1 minute
        if(time >= 3600){   // More or equal to 1 hour
            cout<<"Finish in: "<< time / 3600 <<" hours."<<endl;
        }else{
            cout<<"Finish in: "<< time / 60 <<" minutes."<<endl;
        }
    }else{
        cout<<"Finish in: "<<time<<" seconds."<<endl;
    }


}

