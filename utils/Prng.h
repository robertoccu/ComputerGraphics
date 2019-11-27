//
// Created by Sergio on 27/11/2019.
//

#ifndef COMPUTERGRAPHICS_PRNG_H
#define COMPUTERGRAPHICS_PRNG_H

#include <random>

/**
 * Class to generate pseudo-random number
 */

using namespace std;
class Prng {
public:
    /**
     * Return a random number between [0.0, 1.0]
     * @return
     */
    static float random() {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        static std::uniform_real_distribution<float> dist(0.0, 1.0);

        return dist(mt);
    }
};




#endif //COMPUTERGRAPHICS_PRNG_H
