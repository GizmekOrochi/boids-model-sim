#ifndef BOID_HPP
#define BOID_HPP

#pragma once
#include "Vec2.hpp"

namespace bd {

class Boid {
public:
    Vec2<float> position;
    Vec2<float> velocity;

    Boid() : position(0,0), velocity(0,0) {}
    Boid(float x, float y) : position(x,y), velocity(0,0) {}
};

}


#endif // BOID_HPP
