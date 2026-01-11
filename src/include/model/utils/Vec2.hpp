#ifndef VEC2_HPP
#define VEC2_HPP

#pragma once
#include <cmath>

namespace bd {

template <typename T>
class Vec2 {
public:
    T x;
    T y;

    Vec2() : x(0), y(0) {}
    Vec2(T newx, T newy) : x(newx), y(newy) {}

    Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }
    Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }
    Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }
    Vec2 operator/(T scalar) const {
        if (scalar == T(0)) return Vec2();
        return Vec2(x / scalar, y / scalar);
    }


    bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Vec2& rhs) const {
        return !(*this == rhs);
    }

    Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    Vec2& operator*=(T s) { x *= s; y *= s; return *this; }
    Vec2& operator/=(T s) {
        if (s != T(0)) {
            x /= s;
            y /= s;
        } else {
            x = y = T(0);
        }
        return *this;
    }

    friend Vec2 operator*(T s, const Vec2& v) {
        return Vec2(v.x * s, v.y * s);
    }

    T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }
    T lengthSq() const { return x * x + y * y; }
    T length() const { return std::sqrt(lengthSq()); }

    Vec2 normalized() const {
        T lenSq = lengthSq();
        if (lenSq == T(0)) return Vec2();
        T invLen = T(1) / std::sqrt(lenSq);
        return Vec2(x * invLen, y * invLen);
    }

    bool isZero(T eps = T(1e-6)) const {
        return lengthSq() < eps * eps;
    }

    Vec2 limited(T max) const {
        T lenSq = lengthSq();
        if (lenSq > max * max) {
            T invLen = max / std::sqrt(lenSq);
            return Vec2(x * invLen, y * invLen);
        }
        return *this;
    }
};

}

#endif