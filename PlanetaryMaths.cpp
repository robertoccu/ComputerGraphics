/**
 * Maths done for P1 'FTL'.
 */

#include "maths/Matrix.h"
#include "maths/Vector.h"
#include <cmath>

using namespace std;
class Planet {
public:
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
        Matrix return_to_planet_base;
        return_to_planet_base.setVectors(center_to_city, the_other_vector_as_known_as_vector_Y, center_to_north);
        return_to_planet_base.setPoint(center);

        Vector station = center + center_to_north; // Do rotations at center of UCS.
        station = return_to_planet_base.inverse() * station;    // Move to UCS System
        // Now, station is in UCS system

        Matrix apply_azimuth = Matrix(); apply_azimuth.setRotZ(azimuth);
        Matrix apply_inclination = Matrix(); apply_inclination.setRotY(inclination);
        Matrix positioning = apply_azimuth * apply_inclination; // First apply inclination then azimuth.
        station = positioning * station;

        // Now we must move the point to the planet base
        return return_to_planet_base * station;
    }

    Vector get_vector_to_station(Vector station_planetA, Vector station_planetB){
        // First we obtain the new base from the planetA
        Vector normal_planetA = station_planetA - center;
        // Tangent vector to normal, positive direction from azimuth
        Vector tangent_normal_azimuth = Vector::cross(center_to_north, normal_planetA);
        // Other tangent vector to normal, negative direction from inclination
        Vector tangent_normal_inclination = Vector::cross(tangent_normal_azimuth, normal_planetA);

        // Change bass matrix
        Matrix change_base_stationA;
        change_base_stationA.setVectors(tangent_normal_azimuth, tangent_normal_inclination, normal_planetA);

        // Return the station_planetB in the base_stationA base.
        Vector station_planetB_local_coordinates = (change_base_stationA.inverse() * station_planetB).normalize();
        return station_planetB_local_coordinates;
    }

    Vector get_normal(Vector point_from_planet){
        return point_from_planet - center;
    }
};

int main() {

    Planet planet_1(Vector(0,0,0,1), Vector(0,0,2,0),
            Vector(-1,0,0,1));
    Planet planet_2(Vector(10,0,0,1), Vector(0,0,2,0),
                    Vector(11,0,0,1));

    Vector station_planet1 = planet_1.get_station(M_PI, M_PI_2);
    Vector station_planet2 = planet_2.get_station(M_PI, M_PI_2);

    Vector ray_from_station1_to_station2 = planet_1.get_vector_to_station(station_planet1, station_planet2);

    // Is it possible, pierce the center of planet2?
    if( Vector::dot(ray_from_station1_to_station2,
            planet_2.get_normal(Vector(10,0,0,1))) <= 0){
        // If dot product is negative, collision
        cout<<"Ray from Planet 1 to Planet2 in local coordinates from Planet1: "<<endl;
        cout << ray_from_station1_to_station2 <<endl;
    }else{
        cout<<"Not possible the collision"<<endl;
    }

}