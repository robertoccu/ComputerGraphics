/**
 * Main function
 */

#include <iostream>
#include <ctime>
#include <io.h>
#include "utils/IOppm.h"
#include "imaging/ToneMapper.h"
#include "render/Scene.h"
#include "render/tracer.h"

#ifndef DEBUG_MODE
#define DEBUG_MODE
#endif

using namespace std;

// Constantes
const int PATHS_PER_PIXEL = 64;
const string IMAGE_PATH = "./data";

int main(){
    // Create if not exist the data directory
    mkdir(IMAGE_PATH.c_str());

    unsigned init_time, finish_time;
    // Obtain the timestamp
    init_time = clock();

    // Run the main program
    cout<<"Path tracer: "<<PATHS_PER_PIXEL<<" ppp."<<endl;
    Scene scene;
    scene.load_cornellBox();
    Image image = tracer::ray_tracer(scene, PATHS_PER_PIXEL);    // Create the image
    float max_pixel_value = image.getMaxValue();
    cout<<endl;

    if (max_pixel_value >= 65535) {
        ToneMapper::clamping(image, 65535);
    }
    cout<<"Saving HDR image..."<<endl;
    IOppm::store(IMAGE_PATH + "/ray_tracer_hdr.ppm", image, 10000000);
    cout<<endl;

    cout<<"Tone Mapping image...";
    image.setMaxValue(max_pixel_value);
    //ToneMapper::equalAndClamp(image, 10);
    //ToneMapper::equalization(image);    // Tone mapping
    //ToneMapper::gamma(image, 0.8);
    ToneMapper::clampAndGamma(image, 100, 0.45); // First clamp to light max value.
    //ToneMapper::reinhard(image, RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()),0.18, 0.75);
    cout<<"Done!"<<endl;

    cout<<"Saving (8-bit) image...";
    IOppm::store(IMAGE_PATH + "/ray_tracer.ppm", image, 255);
    cout<<"Done!"<<endl;

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

int main2(){
    // Image I/O test
    Image image = IOppm::read(IMAGE_PATH + "/ray_tracer_hdr.ppm");
    //ToneMapper::clamping(image, 1);
    //ToneMapper::equalization(image);
    //ToneMapper::equalAndClamp(image,100)
    //ToneMapper::gamma(image,0.25);
    ToneMapper::clampAndGamma(image, 100, 0.30);
    //ToneMapper::reinhard(image, RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()),0.18, 0.75);

    // Test
    /*RGB rgb(255,0,0);
    cout<<endl<<"Testing one color conversion"<<endl;
    cout<<"RGB: {"<<rgb.get(RED)<<", "<<rgb.get(GREEN)<<", "<<rgb.get(BLUE)<<"}"<<endl;
    cout<<"xyY: {"<<get<0>(rgb.RGBtoxyY())<<", "<<get<1>(rgb.RGBtoxyY())<<", "<<get<2>(rgb.RGBtoxyY())<<"}"<<endl;
    cout<<"Coincide con los resultados de alguna herramienta web...??"<<endl;*/
    // Test

    image.setMaxValue(1);
    IOppm::store(IMAGE_PATH + "/ray_tracer_hdr_tone-mapper.ppm", image, 255);
    //IOppm::store("../data/output_gamma_1.5_10.ppm", image, 1023);

}
