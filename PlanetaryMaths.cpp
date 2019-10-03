/**
 * Maths done for P1 'FTL'.
 */

#include "maths/Matrix.h"
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

    /**
     * Return the UCS coordinates of the station defined by azimuth and a inclination
     * @param azimuth azimuth in radians
     * @param inclination inclination in radians
     * @return station in UCS coordinates
     */
    Vector get_station(float azimuth, float inclination) {
        Matrix return_to_ucs;
        return_to_ucs.setVectors(center_to_city, the_other_vector_as_known_as_vector_Y, center_to_north);
        return_to_ucs.setPoint(center);

        /* We define a point in the center of the local system, that's why it's 0,0,0.
         * As in the local system, the south-north axis will always be the Z axis,
         * we add the radius of the planet in the Z axis and this way we get to move up the starting point
         * to the local north.*/
        Vector station = Vector(0,0,0,1) +
                Vector(0,0,center_to_north.modulus(),0);

        /* We apply the rotations */
        Matrix apply_azimuth = Matrix(); apply_azimuth.setRotZ(azimuth);
        Matrix apply_inclination = Matrix(); apply_inclination.setRotY(inclination);
        Matrix positioning = apply_azimuth * apply_inclination; // First apply inclination then azimuth.
        station = positioning * station;

        /* We switched to the UCS coordinate system */
        return return_to_ucs * station;
    }

    /**
     * Returns the vector that goes from station A to station B in the local system of station A.
     * @param station_planetA   UCS coordinates of station A
     * @param station_planetB   UCS coordinates of station B
     * @return the vector from station A to stationB
     */
    Vector get_vector_to_station(const Vector &station_planetA, const Vector &station_planetB){
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

    Vector ref_city_planet1 = Vector(-1, 0, 0, 1);
    Vector ref_city_planet2 = Vector(11, 0, 0, 1);

    Planet planet_1(Vector(0,0,0,1), Vector(0,0,2,0),
                    ref_city_planet1);
    Planet planet_2(Vector(10,0,0,1), Vector(0,0,2,0),
                    ref_city_planet2);

    Vector station_planet1 = planet_1.get_station(M_PI, M_PI_2);
    Vector station_planet2 = planet_2.get_station(M_PI, M_PI_2);

    Vector ray_from_station1_to_station2 = planet_1.get_vector_to_station(station_planet1, station_planet2);

    // Is it possible, pierce the center of planet2?
    if( Vector::dot(planet_1.get_normal(station_planet1),
            planet_2.get_normal(station_planet2)) <= 0){
        // Dot product between the normal to station_planet1 and the normal to the station of planet B.
        // If dot product is negative, collision
        cout<<"Ray from Planet 1 to Planet2 in local coordinates from Planet1: "<<endl;
        cout << ray_from_station1_to_station2 <<endl;
        cout<<"Ray from Planet 2 to Planet1 in local coordinates from Planet2: "<<endl;
        cout<< planet_2.get_vector_to_station(station_planet2, station_planet1) <<endl;
    }else{
        cout<<"Not possible the collision"<<endl;
    }

}