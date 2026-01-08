#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../model/utils/MathsVector.hpp"
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

    const MathsVector<float, 3>& getPosition() const;
    float getYaw() const;
    float getPitch() const;

    MathsVector<float, 3> forward() const;
    MathsVector<float, 3> right() const;
    MathsVector<float, 3> up() const;

private:
    MathsVector<float, 3> position{{0.0f, 0.0f, -250.0f}};
    MathsVector<float, 2> rotation{};

    float moveSpeed{settings::moveSpeed};
    float rotSpeed{settings::rotSpeed};

    void clampPitch();
};

} // namespace bd

#endif
