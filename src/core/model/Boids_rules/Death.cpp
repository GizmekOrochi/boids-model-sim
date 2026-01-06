#include "../../../include/model/Boids_rules/Death.hpp"
#include <cmath>
#include <iostream>

namespace bd {

Vec3<float> Death::apply(const Boid& b, const RuleContext& ctx) const {
    if (!ctx.eaten)
        return Vec3<float>(0.f, 0.f, 0.f);

    for (size_t i = 0; i < ctx.predator.getsize(); ++i) {
        const Boid& predator = ctx.boids[ctx.predator[i]];

        if (!canEat(predator.specie, b.specie))
            continue;

        if ((b.position - predator.position).lengthSq() <= settings::eatDistSq) {
            ctx.eaten->push_back(b.ID);
            std::cout << "EATEN " << b.ID << "\n"; 
            break;
        }
    }

    return Vec3<float>(0.f, 0.f, 0.f);
}
} // namespace bd
