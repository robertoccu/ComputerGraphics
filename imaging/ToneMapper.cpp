//
// Created by ccucr on 21/10/2019.
//

#include "ToneMapper.h"
#include <cmath>

void ToneMapper::clamping(Image &image, float clampValue) {
    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED,image.getPixels()[i].get(RED) < clampValue ? image.getPixels()[i].get(RED) : clampValue);

        rgb.set(GREEN,image.getPixels()[i].get(GREEN) < clampValue ? image.getPixels()[i].get(GREEN) : clampValue);

        rgb.set(BLUE,image.getPixels()[i].get(BLUE) < clampValue ? image.getPixels()[i].get(BLUE) : clampValue);

        /*tuple<double,double,double> pixel_xyY = image.getPixels()[i].RGBtoxyY();
        double x = get<0>(pixel_xyY);
        double y = get<1>(pixel_xyY);
        double Y = get<2>(pixel_xyY) < clampValue ? get<2>(pixel_xyY) : clampValue;
        rgb = rgb.xyYtoRGB(make_tuple(x,y,Y));
        image.setPixel(i, rgb);*/
    }
    image.setMaxValue(clampValue);
}

void ToneMapper::equalization(Image &image) {
    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        /*rgb.set(RED,image.getPixels()[i].get(RED) / image.getMaxValue());

        rgb.set(GREEN,image.getPixels()[i].get(GREEN) / image.getMaxValue());

        rgb.set(BLUE,image.getPixels()[i].get(BLUE) / image.getMaxValue());*/

        double maxY = get<2>(RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()).RGBtoxyY());

        tuple<double,double,double> pixel_xyY = image.getPixels()[i].RGBtoxyY();
        double x = get<0>(pixel_xyY);
        double y = get<1>(pixel_xyY);
        double Y = get<2>(pixel_xyY) / maxY;
        rgb = rgb.xyYtoRGB(make_tuple(x,y,Y));

        image.setPixel(i, rgb);
    }
    image.setMaxValue(1);
}

void ToneMapper::equalAndClamp(Image &image, float clampValue) {
    ToneMapper::clamping(image,clampValue);
    ToneMapper::equalization(image);
    image.setMaxValue(1);
}

void ToneMapper::gamma(Image &image, float gamma) {
    ToneMapper::equalization(image);

    RGB rgb = RGB();
    for(int i = 0; i < image.getPixels().size(); i++){
        // Set the pixel
        rgb.set(RED, pow(image.getPixels()[i].get(RED), gamma));

        rgb.set(GREEN,pow(image.getPixels()[i].get(GREEN), gamma));

        rgb.set(BLUE,pow(image.getPixels()[i].get(BLUE), gamma));

        /*double maxY = get<2>(RGB(image.getMaxValue(),image.getMaxValue(),image.getMaxValue()).RGBtoxyY());

        tuple<double,double,double> pixel_xyY = image.getPixels()[i].RGBtoxyY();
        double x = get<0>(pixel_xyY);
        double y = get<1>(pixel_xyY);
        double Y = pow(get<2>(pixel_xyY),gamma);
        rgb = rgb.xyYtoRGB(make_tuple(x,y,Y));*/

        image.setPixel(i, rgb);
    }
    image.setMaxValue(1);

}

void ToneMapper::clampAndGamma(Image &image, float clampValue, float gamma) {
    ToneMapper::clamping(image, clampValue);
    ToneMapper::gamma(image, gamma);
}

void ToneMapper::reinhard(Image &image, const RGB &Lwhite_rgb, const float delta, const float alpha) {

    // Obtain the logMean of the global luminance
    float Lwabsolute  = 0.0;
    float Lwxy = 0.0;
    // Formula 1
    for(const auto & i : image.getPixels()){
        Lwxy = get<2>(i.RGBtoxyY());    // Obtain the luminance of a rgb pixel
        Lwabsolute += log(delta + Lwxy);
    }

    Lwabsolute = exp((Lwabsolute) / image.getPixels().size()); // Lw = e^(log...) / N

    // Reinhard formulation
    float lWhite2 = pow(get<2>(Lwhite_rgb.RGBtoxyY()), 2);
    float lxy, ldxy, x, y;
    RGB output = RGB();
    int iterator = 0;   // Because const auto &i is a colour
    for(const auto &i : image.getPixels()){
        // Formula 2
        lxy = (alpha / Lwabsolute) * get<2>(i.RGBtoxyY());
        x = get<0>(i.RGBtoxyY());
        y = get<1>(i.RGBtoxyY());

        // Ld(x, y) from reinhard formule
        ldxy = (lxy * (1 + (lxy / lWhite2))) / (1 + lxy);

        // Make the new rgb
        output = output.xyYtoRGB(make_tuple(x,y, ldxy));
        image.setPixel(iterator, output);
        iterator++;
    }

}