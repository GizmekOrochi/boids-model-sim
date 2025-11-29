#include <iostream>
#include <cassert>
#include "../src/include/model/Vec2.hpp"

int main() {
    using bd::Vec2;

    // Test constructor
    Vec2<float> a;
    assert(a.x == 0.0f && a.y == 0.0f);

    Vec2<float> b(3.0f, 4.0f);
    assert(b.x == 3.0f && b.y == 4.0f);

    // Test opperator
    Vec2<float> c = a + b;
    assert(c.x == 3.0f && c.y == 4.0f);

    Vec2<float> d = b - Vec2<float>(1.0f, 2.0f);
    assert(d.x == 2.0f && d.y == 2.0f);

    Vec2<float> e = b * 2.0f;
    assert(e.x == 6.0f && e.y == 8.0f);

    Vec2<float> f = b / 2.0f;
    assert(f.x == 1.5f && f.y == 2.0f);

    Vec2<float> g(1, 1);
    g += Vec2<float>(2, 3);
    assert(g.x == 3 && g.y == 4);

    g -= Vec2<float>(1, 1);
    assert(g.x == 2 && g.y == 3);

    g *= 2;
    assert(g.x == 4 && g.y == 6);

    g /= 2; 
    assert(g.x == 2 && g.y == 3);

    // test compareson
    assert(Vec2<int>(1, 2) == Vec2<int>(1, 2));
    assert(Vec2<int>(1, 2) != Vec2<int>(2, 1));

    // Test comparaison
    assert(b.length() == 5.0f);

    // Test normalisation
    Vec2<float> n = b.normalized();
    assert(std::abs(n.length() - 1.0f) < 0.0001f);

    // Normalisation nul vecctor
    Vec2<float> zero(0, 0);
    Vec2<float> nz = zero.normalized();
    assert(nz.x == 0 && nz.y == 0);

    std::cout << "Vec2 tests passed. The class works.\n";
    return 0;
}
