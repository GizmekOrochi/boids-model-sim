#ifndef COHESION_HPP
#define COHESION_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Cohesion : public Rule {
public:

    MathsVector<float, 3> apply(const Boid& b, const RuleContext& ctx) const override;
};

}

#endif // COHESION_HPP