#include "../../../include/model/Boids_rules/Cohesion.hpp"

namespace bd {

Vec3<float> Cohesion::apply(const Boid& b, const RuleContext& ctx) const {
    if (ctx.neighbors.getsize() == 0)
        return Vec3<float>(0.0f, 0.0f, 0.0f);

    Vec3<float> center(0.0f, 0.0f, 0.0f);
    float totalWeight = 0.0f;

    for (size_t i = 0; i < ctx.neighbors.getsize(); ++i) {
        const Boid& other = ctx.boids[ctx.neighbors[i]];

        // Predator prey hunger boost
        float hungerspeedfactor = 1.0f;
        if (canEat(b.specie, other.specie)) {
            hungerspeedfactor = static_cast<float>(speciesTier(b.specie));
        }

        center += other.position * hungerspeedfactor;
        totalWeight += hungerspeedfactor;
    }

    if (totalWeight <= 0.0f)
        return Vec3<float>(0.0f, 0.0f, 0.0f);

    center /= totalWeight;

    Vec3<float> steer = center - b.position;
    return steer * settings::cohesionWeight;
}

} // namespace

