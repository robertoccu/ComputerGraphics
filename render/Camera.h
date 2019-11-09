//
// Created by Sergio on 08/11/2019.
//

#ifndef COMPUTERGRAPHICS_CAMERA_H
#define COMPUTERGRAPHICS_CAMERA_H

#include "../maths/Vector.h"

/**
 * The camera class represents a pinhole camera. It is composed of a 3D point where the light arrives,
 * and three vectors (Not unitary, since they are the ones that define the size of the screen or image).
 * Up vector to the top of the camera, left vector to the left of the camera and forward that goes to the screen.
 */
class Camera {
    Vector position, up, left, forward;

public:
    Camera(const Vector &position, const Vector &up, const Vector &left, const Vector &forward);

    Camera();

    const Vector &getPosition() const;

    void setPosition(const Vector &position);

    const Vector &getUp() const;

    void setUp(const Vector &up);

    const Vector &getLeft() const;

    void setLeft(const Vector &left);

    const Vector &getForward() const;

    void setForward(const Vector &forward);
};


#endif //COMPUTERGRAPHICS_CAMERA_H
