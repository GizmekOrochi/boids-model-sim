#ifndef SEPARATION_HPP
#define SEPARATION_HPP

#pragma once
#include "Rule.hpp"

namespace bd {

class Separation : public Rule {
public:

    MathsVector<float, 3> apply(const Boid& b, const RuleContext& ctx) const override;
};

}


#endif // SEPARATION_HPP