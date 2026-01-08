#ifndef WORLD_HPP
#define WORLD_HPP

#pragma once
#include "Boid.hpp"
#include "../config/Settings.hpp"
#include "utils/MathsVector.hpp"

namespace bd {

class World {
public:

    World() : size{{settings::worldWidth, settings::worldHeight, settings::worldDeepth}} {};
    World(MathsVector<float, 3> size) : size{size} {}

    float getWidth() const { return size[0]; }
    float getHeight() const { return size[1]; }
    float getDepth() const { return size[2]; }

    void handleBoundaries(Boid& b) const;

private:
    MathsVector<float, 3> size;
};

}

#endif // WORLD_HPP