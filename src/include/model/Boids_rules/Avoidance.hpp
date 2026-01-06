#ifndef AVOIDANCE_HPP
#define AVOIDANCE_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Avoidance : public Rule {
public:
    Vec3<float> apply(const Boid& b, const RuleContext& ctx) const;
};

}


#endif // AVOIDANCE_HPP
