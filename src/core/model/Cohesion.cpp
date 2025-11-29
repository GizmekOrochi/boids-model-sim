#include "../../include/model/Cohesion.hpp"
#include "../../include/model/Vec2.hpp"
#include "../../include/model/Boid.hpp"

namespace bd {

Vec2<float> Cohesion::apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const {
    size_t count = neighbors.getsize();
    if (count == 0) {
        return Vec2<float>(0.0f, 0.0f);
    }

    Vec2<float> center(0.0f, 0.0f);
    for (size_t i = 0; i < count; ++i) {
        center += neighbors[i].position;
    }
    center /= static_cast<float>(count);

    // Direction from current boid to the center of mass
    Vec2<float> steering = center - boid.position;
    return steering * weight;
}

}
