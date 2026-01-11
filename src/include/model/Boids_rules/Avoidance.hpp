#ifndef AVOIDANCE_HPP
#define AVOIDANCE_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Avoidance : public Rule {
    public:

        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const;

    private:

        Vec3<float> avoidWorldBounds(const Boid& b) const;
        Vec3<float> avoidObstacles(const Boid& b, const RuleContext& ctx) const;
        Vec3<float> avoidPredators(const Boid& b, const RuleContext& ctx) const;
    };

}


#endif // AVOIDANCE_HPP