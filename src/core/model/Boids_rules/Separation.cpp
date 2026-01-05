#include "../../../include/model/Boids_rules/Separation.hpp"
#include "../../../include/model/Boid.hpp"

namespace bd {

Vec3<float> Separation::apply(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const {
    if (neighbors.getsize() == 0)
        return Vec3<float>(0.f, 0.f, 0.f);

    Vec3<float> steer(0.f, 0.f, 0.f);

    for (size_t i = 0; i < neighbors.getsize(); ++i) {
        const Boid& n = boids[neighbors[i]];

        Vec3<float> diff = b.position - n.position;
        float dist = diff.length();

        if (dist > 0.f)
            steer += diff.normalized() / dist;
    }

    return steer * weight;
}

}