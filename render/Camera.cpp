//
// Created by Sergio on 08/11/2019.
//

#include "Camera.h"

Camera::Camera(const Vector &position, const Vector &up, const Vector &left, const Vector &forward) : position(
        position), up(up), left(left), forward(forward) {}

const Vector &Camera::getPosition() const {
    return position;
}

void Camera::setPosition(const Vector &position) {
    Camera::position = position;
}

const Vector &Camera::getUp() const {
    return up;
}

void Camera::setUp(const Vector &up) {
    Camera::up = up;
}

const Vector &Camera::getLeft() const {
    return left;
}

void Camera::setLeft(const Vector &left) {
    Camera::left = left;
}

const Vector &Camera::getForward() const {
    return forward;
}

void Camera::setForward(const Vector &forward) {
    Camera::forward = forward;
}

Camera::Camera() = default;
