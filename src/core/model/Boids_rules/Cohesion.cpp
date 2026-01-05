#include "../../../include/model/Boids_rules/Cohesion.hpp"
#include "../../../include/model/Boid.hpp"

namespace bd {

Vec3<float> Cohesion::apply(const Boid& b, const DynamicArray<size_t>& neighbors, const DynamicArray<Boid>& boids) const {
    if (neighbors.getsize() == 0)
        return Vec3<float>(0.f, 0.f, 0.f);

    Vec3<float> center(0.f, 0.f, 0.f);

    for (size_t i = 0; i < neighbors.getsize(); ++i) {
        center += boids[neighbors[i]].position;
    }

    center /= static_cast<float>(neighbors.getsize());

    Vec3<float> steer = center - b.position;
    return steer * weight;
}

}
