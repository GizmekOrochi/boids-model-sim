#include "../../include/model/Separation.hpp"
#include "../../include/model/Vec2.hpp"
#include "../../include/model/Boid.hpp"


namespace bd {

Vec2<float> Separation::apply(const Boid& boid, const DynamicArray<Boid>& neighbors) const {
    Vec2<float> force(0.0f, 0.0f);
    size_t count = neighbors.getsize();

    for (size_t i = 0; i < count; ++i) {
        const Boid& other = neighbors[i];
        Vec2<float> diff = boid.position - other.position;
        float distSq = diff.x * diff.x + diff.y * diff.y;

        if (distSq > 0.0f && distSq < (desiredDistance * desiredDistance)) {
            // inverse-square repulsion
            force += diff / distSq;
        }
    }

    return force * weight;
}

}