/**
 * Main function
 */

#include <iostream>
#include <ctime>
#include "maths/Matrix.h"
#include "geometry/Ray.h"
#include "geometry/Sphere.h"
#include "utils/PlanetaryMaths.h"
#include "utils/IOppm.h"
#include "imaging/ToneMapper.h"

using namespace std;

int main(){
    unsigned init_time, finish_time;
    // Obtain the timestamp
    init_time = clock();

    // Run the main program
    cout<<"COMPUTER GRAPHICS"<<endl;

    // Planetary Maths (matrix training)
    //planetary_main();

    // Image I/O test
    Image image = IOppm::read("../data/hdr-ppm/seymour_park.ppm");
    //ToneMapper::clamping(image, 1);
    //ToneMapper::equalization(image);
    //ToneMapper::equalAndClamp(image,40000);
    //ToneMapper::gamma(image,1.5);
    //ToneMapper::clampAndGamma(image, 50000, 1.8);
    ToneMapper::reinhard(image, RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()));
    image.setMaxValue(1);
    IOppm::store("../data/output_r.ppm", image, 255);
    //IOppm::store("../data/output_gamma_1.5_10.ppm", image, 1023);

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

