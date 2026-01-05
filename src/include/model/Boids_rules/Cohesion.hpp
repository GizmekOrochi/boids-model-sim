#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"
#include "../utils/Vec2.hpp"
#include "../../config/Settings.hpp"

namespace bd {

class Cohesion : public Rule {
public:
    float weight = settings::cohesionWeight;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}

#endif // COHESION_HPP
