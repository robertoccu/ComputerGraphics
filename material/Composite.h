#ifndef COMPUTERGRAPHICS_COMPOSITE_H
#define COMPUTERGRAPHICS_COMPOSITE_H


#include "Material.h"
#include "Emitter.h"
#include "Phong.h"

/**
 * Represents a material composed of Phong,
 * Emission, Specular Perfect and Refraction perfect.
 */
class Composite : public Material{
    Emitter emitter;
    Phong phong;
    // TODO: SPECULAR PERFECT AND REFRACTION PERFECT
public:
    Composite(const Emitter& emitter, const Phong &phong){this->emitter = emitter; this->phong = phong;}
    Composite() {emitter = Emitter(); phong = Phong();}
    RGB get_emision() override{ return emitter.get_emision(); }
};
#endif //COMPUTERGRAPHICS_COMPOSITE_H
