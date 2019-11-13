/**
 * Main function
 */

#include <iostream>
#include <ctime>
#include "utils/IOppm.h"
#include "imaging/ToneMapper.h"
#include "render/Scene.h"
#include "render/tracer.h"

using namespace std;

int main(){
    unsigned init_time, finish_time;
    // Obtain the timestamp
    init_time = clock();

    // Run the main program
    const int PATHS_PER_PIXEL = 1;
    Scene scene;
    scene.load_scene1();
    Image image = tracer::ray_tracer(scene, PATHS_PER_PIXEL);    // Create the image

    ToneMapper::equalization(image);    // Tone mapping
    IOppm::store("../data/ray_tracer.ppm", image, 255);


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



void tone_mapper(){
    // Image I/O test
    Image image = IOppm::read("../data/hdr-ppm/seymour_park.ppm");
    //ToneMapper::clamping(image, 1);
    //ToneMapper::equalization(image);
    //ToneMapper::equalAndClamp(image,40000);
    //ToneMapper::gamma(image,1.5);
    //ToneMapper::clampAndGamma(image, 50000, 1.8);
    //ToneMapper::reinhard(image, RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()),
    //      0.18, 0.18);

    // Test
    RGB rgb(255,0,0);
    cout<<endl<<"Testing one color conversion"<<endl;
    cout<<"RGB: {"<<rgb.get(RED)<<", "<<rgb.get(GREEN)<<", "<<rgb.get(BLUE)<<"}"<<endl;
    cout<<"xyY: {"<<get<0>(rgb.RGBtoxyY())<<", "<<get<1>(rgb.RGBtoxyY())<<", "<<get<2>(rgb.RGBtoxyY())<<"}"<<endl;
    cout<<"Coincide con los resultados de alguna herramienta web...??"<<endl;
    // Test

    image.setMaxValue(1);
    IOppm::store("../data/output_r.ppm", image, 255);
    //IOppm::store("../data/output_gamma_1.5_10.ppm", image, 1023);

}


