#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once
#include "Boid.hpp"

namespace bd {

class World {
private:
    float width;
    float height;

public:
    World(float w = 0.0f, float h = 0.0f);

    float getWidth() const;
    float getHeight() const;

    void handleBoundaries(Boid& b) const;
};

}

#endif // WORLD_HPP
