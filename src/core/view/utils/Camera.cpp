#include "../../../include/view/utils/Camera.hpp"

namespace bd {

Camera::Camera() = default;

float Camera::getYaw() const {
    return rotation[0];
}

float Camera::getPitch() const {
    return rotation[1];
}

void Camera::moveForward(float dt) {
    position += forward() * (moveSpeed * dt);
}

void Camera::moveRight(float dt) {
    position += right() * (moveSpeed * dt);
}

void Camera::moveUp(float dt) {
    position[1] += moveSpeed * dt;
}

void Camera::rotate(float dyaw, float dpitch) {
    rotation[0] += dyaw * rotSpeed;
    rotation[1] += dpitch * rotSpeed;
    clampPitch();
}

void Camera::clampPitch() {
    rotation[0] = std::clamp(rotation[0], -1.45f, 1.45f);
}

const MathsVector<float, 3>& Camera::getPosition() const {
    return position;
}

MathsVector<float, 3> Camera::forward() const {
    float cy{std::cos(rotation[0])}; 
    float sy{std::sin(rotation[0])};
    float cp{std::cos(rotation[1])};
    float sp{std::sin(rotation[1])};
    return MathsVector<float, 3>{{sy * cp, -sp, cy * cp}};
}

MathsVector<float, 3> Camera::right() const {
    float cy = std::cos(rotation[0]), sy = std::sin(rotation[0]);
    return MathsVector<float, 3>{{cy, 0.0f, -sy}};
}

MathsVector<float, 3> Camera::up() const {
    return MathsVector<float, 3>{{0.0f, 1.0f, 0.0f}};
}

} // namespace bd
