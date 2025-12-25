#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"
#include "Vec2.hpp"
#include "../config/Settings.hpp"

namespace bd {

class Cohesion : public Rule {
private:
    Settings settings;
public:
    float weight = settings.cohesionweight;

    Vec2<float> apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const override;
};

}

#endif // COHESION_HPP
