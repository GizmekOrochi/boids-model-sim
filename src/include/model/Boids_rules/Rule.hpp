#ifndef RULE_HPP
#define RULE_HPP

#include "RuleContext.hpp"

namespace bd {

class Rule {
public:
    virtual ~Rule() = default;

    virtual Vec3<float> apply(const Boid& b, const RuleContext& ctx) const = 0;

};

}


#endif // RULE_HPP