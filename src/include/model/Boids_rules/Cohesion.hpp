#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec3.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Cohesion : public Rule {
public:
    float weight = settings::cohesionWeight;

    Vec3<float> apply(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const override;
};

}

#endif // COHESION_HPP
