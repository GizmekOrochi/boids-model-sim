#ifndef AVOIDANCE_HPP
#define AVOIDANCE_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Avoidance : public Rule {
public:

    MathsVector<float, 3> apply(const Boid& b, const RuleContext& ctx) const;

private:

    MathsVector<float, 3> avoidWorldBounds(const Boid& b) const;
    MathsVector<float, 3> avoidObstacles(const Boid& b, const RuleContext& ctx) const;
    MathsVector<float, 3> avoidPredators(const Boid& b, const RuleContext& ctx) const;
};

}


#endif // AVOIDANCE_HPP