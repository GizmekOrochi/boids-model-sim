#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../model/utils/Vec3.hpp"
#include "../../config/Settings.hpp"
#include <algorithm>
#include <cmath>

namespace bd {

class Camera {
public:
    Camera();

    void moveForward(float dt);
    void moveRight(float dt);
    void moveUp(float dt);

    void rotate(float deltaYaw, float deltaPitch);

    const Vec3<float>& getPosition() const;
    float getYaw() const;
    float getPitch() const;

    Vec3<float> forward() const;
    Vec3<float> right() const;
    Vec3<float> up() const;

private:
    void clampPitch();

private:
    Vec3<float> position {0.f, 0.f, -250.f};
    float yaw = 0.f;
    float pitch = 0.f;

    float moveSpeed = settings::moveSpeed;
    float rotSpeed  = settings::rotSpeed;
};

} // namespace bd

#endif
