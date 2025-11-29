#include <iostream>
#include <cassert>

// Your headers
#include "../src/include/model/Boid.hpp"
#include "../src/include/model/Cohesion.hpp"
#include "../src/include/model/Separation.hpp"
#include "../src/include/model/Alignment.hpp"
#include "../src/include/model/Flock.hpp"
#include "../src/include/model/DynamicArray.hpp"
#include "../src/include/model/Vec2.hpp"

using namespace bd;

int main() {

    // test Boid structure
    {
        Boid b(10, 20);
        assert(b.position.x == 10);
        assert(b.position.y == 20);
        assert(b.velocity.x == 0);
        assert(b.velocity.y == 0);
        std::cout << "[OK] Boid basic construction\n";
    }

    // test cohesion rule
    {
        Cohesion coh;
        coh.weight = 1.0f;

        Boid self(0, 0);

        DynamicArray<Boid> neighbors;
        neighbors.push_back(Boid(10, 0));
        neighbors.push_back(Boid(0, 10));

        Vec2<float> result = coh.apply(self, neighbors);

        // Expected direction (5,5)
        assert(result.x == 5.0f);
        assert(result.y == 5.0f);

        std::cout << "[OK] Cohesion rule\n";
    }

    // test alignment rule
    {
        Alignment ali;
        ali.weight = 1.0f;

        Boid self(0, 0);
        self.velocity = Vec2<float>(0, 0);

        Boid n1(0,0); n1.velocity = Vec2<float>(2, 0);
        Boid n2(0,0); n2.velocity = Vec2<float>(0, 4);

        DynamicArray<Boid> neighbors;
        neighbors.push_back(n1);
        neighbors.push_back(n2);

        Vec2<float> result = ali.apply(self, neighbors);

        // Expected average (1,2)
        assert(result.x == 1.0f);
        assert(result.y == 2.0f);

        std::cout << "[OK] Alignment rule\n";
    }

    // test Separation rule
    {
        Separation sep;
        sep.weight = 1.0f;
        sep.desiredDistance = 5.0f;

        Boid self(0, 0);

        DynamicArray<Boid> neighbors;
        neighbors.push_back(Boid(2, 0));
        neighbors.push_back(Boid(0, 3));

        Vec2<float> result = sep.apply(self, neighbors);

        // expected result (-0.5, -0.3333)
        assert(result.x < 0);
        assert(result.y < 0);

        std::cout << "[OK] Separation rule\n";
    }

    // test rule polymorphism
    {
        Rule* r = new Cohesion();
        Boid self(0,0);

        DynamicArray<Boid> neigh;
        neigh.push_back(Boid(4, 0));

        Vec2<float> result = r->apply(self, neigh);
        assert(result.x == 4.0f && result.y == 0.0f);

        delete r;

        std::cout << "[OK] Rule polymorphism\n";
    }

    // test Flock structure
    {
        Flock flock;

        flock.addBoid(Boid(1,2));
        flock.addBoid(Boid(3,4));

        class DummyRule : public Rule {
        public:
            Vec2<float> apply(const Boid&, const DynamicArray<Boid>&) const override {
                return Vec2<float>(0,0);
            }
        };

        DummyRule* rule = new DummyRule();
        flock.addRule(rule);

        assert(flock.getBoids().getsize() == 2);

        std::cout << "[OK] Flock structure test\n";
    }

    std::cout << "\nAll model tests passed successfully.\n";
    return 0;
}
