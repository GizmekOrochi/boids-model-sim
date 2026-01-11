#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Alignment : public Rule {
    public:
        Vec3<float> apply(const Boid& b, const RuleContext& ctx) const override;
    };

}


#endif // ALIGNMENT_HPP