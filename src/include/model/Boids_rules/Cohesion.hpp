#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Cohesion : public Rule {
public:
    float weight = settings::cohesionWeight;

    Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
};

}

#endif // COHESION_HPP
