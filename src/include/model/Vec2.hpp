#ifndef VEC2_HPP
#define VEC2_HPP

#pragma once
#include <string>
#include <cmath>

namespace bd {

template <typename T>
class Vec2 {
public:
    T x;
    T y;

    Vec2() : x(0), y(0) {}
    Vec2(T newx, T newy) : x(newx), y(newy) {}

    // Opperators
    Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
    Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
    Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2 operator/(T scalar) const { return Vec2(x / scalar, y / scalar); }

    Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Vec2& operator*=(T s) { x *= s; y *= s; return *this; }
    Vec2& operator/=(T s) { x /= s; y /= s; return *this; }

    bool operator==(const Vec2& rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Vec2& rhs) const { return !(*this == rhs); }

    // dot product
    T dot(const Vec2& rhs) const { return x*rhs.x + y*rhs.y; }

    // norme
    T length() const { return std::sqrt(x*x + y*y); }

    // normatization
    Vec2 normalized() const {
        T len = length();
        return (len != 0) ? Vec2(x/len, y/len) : Vec2();
    }
};

}

#endif // VEC2_HPP
