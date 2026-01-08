#include "../../../include/model/Boids_rules/Death.hpp"
#include <cmath>
#include <iostream>

namespace bd {

MathsVector<float, 3> Death::apply(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};
    if (!ctx.eaten)
        return null;

    for (size_t i = 0; i < ctx.predator.getsize(); ++i) {
        const Boid& predator{ctx.boids[ctx.predator[i]]};

        if (!canEat(predator.specie, b.specie))
            continue;

        if ((b.position - predator.position).lengthSq() <= settings::eatDistSq) {
            ctx.eaten->push_back(b.ID);
            std::cout << "EATEN " << b.ID << "\n"; 
            break;
        }
    }

    return null;
}
} // namespace
