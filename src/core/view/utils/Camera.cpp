#include "../../../include/view/utils/Camera.hpp"

namespace bd {

Camera::Camera() = default;

void Camera::moveForward(float dt) {
    position += forward() * (moveSpeed * dt);
}

void Camera::moveRight(float dt) {
    position += right() * (moveSpeed * dt);
}

void Camera::moveUp(float dt) {
    position.y += moveSpeed * dt;
}

void Camera::rotate(float dyaw, float dpitch) {
    yaw   += dyaw * rotSpeed;
    pitch += dpitch * rotSpeed;
    clampPitch();
}

void Camera::clampPitch() {
    pitch = std::clamp(pitch, -1.45f, 1.45f);
}

const Vec3<float>& Camera::getPosition() const {
    return position;
}

float Camera::getYaw() const {
    return yaw;
}

float Camera::getPitch() const {
    return pitch;
}

Vec3<float> Camera::forward() const {
    float cy = std::cos(yaw), sy = std::sin(yaw);
    float cp = std::cos(pitch), sp = std::sin(pitch);
    return { sy * cp, -sp, cy * cp };
}

Vec3<float> Camera::right() const {
    float cy = std::cos(yaw), sy = std::sin(yaw);
    return { cy, 0.f, -sy };
}

Vec3<float> Camera::up() const {
    return {0.f, 1.f, 0.f};
}

} // namespace bd
