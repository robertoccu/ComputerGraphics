/**
 * Maths done for P1 'FTL'.
 */

#include "maths/Matrix.h"
#include "maths/Vector.h"
#include <cmath>

class Planet {
private:
    Vector center;
    Vector center_to_north; // planet base vector Z
    Vector center_to_city; // planet base vector X
    Vector the_other_vector_as_known_as_vector_Y; // planet base vector Y

public:
    Planet(const Vector &center, const Vector &south_to_north, const Vector &ref_city) {
        this->center = center;
        this->center_to_north = (south_to_north/2).normalize();
        this->center_to_city = (ref_city - center).normalize();
        this->the_other_vector_as_known_as_vector_Y = Vector::cross(center_to_north, center_to_city).normalize(); // East to West (or West to East?)
    }

    Vector get_station(float azimuth, float inclination) {
        Vector station = Vector(0,0,0,1) + center_to_north; // Do rotations at center of UCS.
        Matrix apply_azimuth = Matrix(); apply_azimuth.setRotZ(azimuth);
        Matrix apply_inclination = Matrix(); apply_inclination.setRotY(inclination);
        Matrix positioning = apply_azimuth * apply_inclination; // First apply inclination then azimuth.
        station = positioning * station;
        Matrix return_to_planet_base;
        return_to_planet_base.setVectors(center_to_city, the_other_vector_as_known_as_vector_Y, center_to_north);
        return_to_planet_base.setPoint(center);
        return return_to_planet_base * station;
    }
};

int main() {
    Planet planet_1(Vector(0,0,0,1), Vector(2,0,0,0), Vector(0,0,-1,1));
    Planet planet_2(Vector(10,0,0,1), Vector(0,0,2,0), Vector(11,0,0,1));
    std::cout << planet_1.get_station(0, 0);

}