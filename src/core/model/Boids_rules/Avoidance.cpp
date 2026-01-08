#include "../../../include/model/Boids_rules/Avoidance.hpp"

namespace bd {

constexpr float wallMargin = 30.0f;
constexpr float obstacleGain = 1.2f;
constexpr float predatorGain = 2.5f;
constexpr float weight = 1.5f;
constexpr float radius = 10.0f;

MathsVector<float, 3> Avoidance::apply(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};

    null += avoidWorldBounds(b);
    null += avoidObstacles(b, ctx);
    null += avoidPredators(b, ctx);

    if (null.lengthSq() > 0.f)
        return null.normalized() * weight;
    return null;
}


MathsVector<float, 3> Avoidance::avoidWorldBounds(const Boid& b) const {
    MathsVector<float, 3> null{};

    // X
    if (b.position[0] < wallMargin)
        null[0] += (wallMargin - b.position[0]) / wallMargin;
    else if (b.position[0] > settings::worldWidth - wallMargin)
        null[0] -= (b.position[0] - (settings::worldWidth - wallMargin)) / wallMargin;

    // Y
    if (b.position[1] < wallMargin)
        null[1] += (wallMargin - b.position[1]) / wallMargin;
    else if (b.position[1] > settings::worldHeight - wallMargin)
        null[1] -= (b.position[1] - (settings::worldHeight - wallMargin)) / wallMargin;

    // Z
    if (b.position[2] < wallMargin)
        null[2] += (wallMargin - b.position[2]) / wallMargin;
    else if (b.position[2] > settings::worldDeepth - wallMargin)
        null[2] -= (b.position[2] - (settings::worldDeepth - wallMargin)) / wallMargin;

    return null;
}

MathsVector<float, 3> Avoidance::avoidObstacles(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};
    const float minDist{radius + wallMargin};

    for (size_t i = 0; i < ctx.obstacles.getsize(); ++i) {
        const Obstacle& obs{ctx.obstacles[i]};

        const float hx{obs.size[0] * 0.5f};
        const float hy{obs.size[1] * 0.5f};
        const float hz{obs.size[2] * 0.5f};

        MathsVector<float, 3> closest{{
            std::max(obs.position[0] - hx, std::min(b.position[0], obs.position[0] + hx)),
            std::max(obs.position[1] - hy, std::min(b.position[1], obs.position[1] + hy)),
            std::max(obs.position[2] - hz, std::min(b.position[2], obs.position[2] + hz))
        }};

        MathsVector<float, 3> diff{b.position - closest};
        float distSq{diff.lengthSq()};
        
        // Faire gaff à diff.isZero(distSq), c'est peu être faux
        if (distSq < minDist * minDist && diff.isZero(distSq)) {
            float dist{std::sqrt(distSq)};
            null +=  (diff / dist) * (1.f - dist / minDist) * obstacleGain;
        }
    }

    return null;
}

MathsVector<float, 3> Avoidance::avoidPredators(const Boid& b, const RuleContext& ctx) const {
    MathsVector<float, 3> null{};
    const float perceptionSq{settings::perceptionRadius * settings::perceptionRadius};

    for (size_t i = 0; i < ctx.predator.getsize(); ++i) {
        const Boid& predator{ctx.boids[ctx.predator[i]]};

        MathsVector<float, 3> diff{b.position - predator.position};
        float distSq{diff.lengthSq()};

        if (distSq < perceptionSq && distSq > 1e-6f) {
            float dist = std::sqrt(distSq);
            float strength = 1.0f - dist / settings::perceptionRadius;
            null += (diff / dist) * strength * predatorGain;
        }
    }

    return null;
}

} // namespace
