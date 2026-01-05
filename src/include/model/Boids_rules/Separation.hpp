#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec3.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Separation : public Rule {
public:
    float desiredDistance = settings::desiredDistance;
    float weight = settings::separationWeight;

    Vec3<float> apply(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const override;
};

}


#endif // SEPARATION_HPP
