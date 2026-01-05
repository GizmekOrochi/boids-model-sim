#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../model/utils/Vec3.hpp"
#include <algorithm>


namespace bd {

struct Camera {
    Vec3<float> position {0.f, 0.f, -250.f}; // start a bit back
    float yaw   = 0.f;   // radians
    float pitch = 0.f;   // radians

    float moveSpeed = 250.f; // units/s
    float rotSpeed  = 1.6f;  // rad/s

    Vec3<float> forward() const {
        // yaw about Y axis? We'll use yaw about Z? For screen convention, use yaw about Y (turn left/right in XZ plane)
        // Here: X right, Y up, Z forward (into screen). We'll set forward based on yaw (around Y) and pitch (around X).
        float cy = std::cos(yaw), sy = std::sin(yaw);
        float cp = std::cos(pitch), sp = std::sin(pitch);
        return Vec3<float>{ sy * cp, -sp, cy * cp }; // forward in +Z when yaw=0
    }

    Vec3<float> right() const {
        // right is perpendicular to forward on XZ plane for yaw (ignore pitch for strafing)
        float cy = std::cos(yaw), sy = std::sin(yaw);
        return Vec3<float>{ cy, 0.f, -sy };
    }

    Vec3<float> up() const {
        return Vec3<float>{0.f, 1.f, 0.f};
    }

    void clampPitch() {
        pitch = std::clamp(pitch, -1.45f, 1.45f);
    }
};

} // namespace bd

#endif