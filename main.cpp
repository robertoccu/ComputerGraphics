/**
 * Main function
 */

#include <iostream>
#include <ctime>
#include "utils/IOppm.h"
#include "imaging/ToneMapper.h"
#include "render/Scene.h"
#include "render/tracer.h"

#ifndef DEBUG_MODE
#define DEBUG_MODE
#endif

using namespace std;

int main(){
    unsigned init_time, finish_time;
    // Obtain the timestamp
    init_time = clock();

    // Run the main program
    const int PATHS_PER_PIXEL = 8;
    cout<<"Path tracer: "<<PATHS_PER_PIXEL<<" ppp."<<endl;
    Scene scene;
    scene.load_cornellBox();
    Image image = tracer::ray_tracer(scene, PATHS_PER_PIXEL);    // Create the image
    cout<<endl;

    cout<<"Saving HDR image..."<<endl;
    IOppm::store("../data/ray_tracer_hdr.ppm", image, 65535);
    cout<<endl;

    cout<<"Tone Mapping image..."<<endl;
    //ToneMapper::equalization(image);    // Tone mapping
    ToneMapper::gamma(image, 0.75);
    //ToneMapper::reinhard(image, RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()),0.18, 0.72);
    cout<<endl;

    cout<<"Saving (8-bit) image..."<<endl;
    IOppm::store("../data/ray_tracer.ppm", image, 255);
    cout<<endl;

    /*cout<<"Saving (10-bit) image..."<<endl; // Robert things
    IOppm::store("../data/ray_tracer_10bit.ppm", image, 1023);
    cout<<endl;*/


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
    //     0.18, 0.18);

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


