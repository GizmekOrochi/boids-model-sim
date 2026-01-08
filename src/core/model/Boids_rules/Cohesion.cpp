#include "../../../include/model/Boids_rules/Cohesion.hpp"

namespace bd {

MathsVector<float, 3> Cohesion::apply(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};
    if (ctx.neighbors.getsize() == 0)
        return null;

    MathsVector<float, 3> center{};
    float totalWeight{};

    for (size_t i = 0; i < ctx.neighbors.getsize(); ++i) {
        const Boid& other{ctx.boids[ctx.neighbors[i]]};

        // Predator prey hunger boost
        float hungerspeedfactor{1.0f};
        if (canEat(b.specie, other.specie)) {
            hungerspeedfactor = static_cast<float>(speciesTier(b.specie));
        }

        center += other.position * hungerspeedfactor;
        totalWeight += hungerspeedfactor;
    }

    if (totalWeight <= 0.0f)
        return null;

    center /= totalWeight;

    MathsVector<float, 3> res{center - b.position};
    return res * settings::cohesionWeight;
}

} // namespace

