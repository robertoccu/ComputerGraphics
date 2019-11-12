//
// Created by Sergio on 12/11/2019.
//

#include "Emitter.h"

Emitter::Emitter(const RGB &color) {
    this->color_emitter = color;
}

RGB Emitter::get_emision() {
    return color_emitter;
}


