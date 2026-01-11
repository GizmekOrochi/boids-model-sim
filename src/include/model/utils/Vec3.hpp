#ifndef VEC3_HPP
#define VEC3_HPP

#pragma once
#include <cmath>

namespace bd {

template <typename T>
class Vec3 {
public:
    T x;
    T y;
    T z;

    Vec3() : x(0), y(0), z(0) {}
    Vec3(T newx, T newy, T newz) : x(newx), y(newy), z(newz) {}

    Vec3 operator+(const Vec3& rhs) const {
        return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    Vec3 operator-(const Vec3& rhs) const {
        return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Vec3 operator*(T scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    Vec3 operator/(T scalar) const {
        if (scalar == T(0)) return Vec3();
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    bool operator==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=(const Vec3& rhs) const {
        return !(*this == rhs);
    }

    Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }

    Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x; y -= rhs.y; z -= rhs.z;
        return *this;
    }

    Vec3& operator*=(T s) {
        x *= s; y *= s; z *= s;
        return *this;
    }

    Vec3& operator/=(T s) {
        if (s != T(0)) {
            x /= s; y /= s; z /= s;
        } else {
            x = y = z = T(0);
        }
        return *this;
    }

    friend Vec3 operator*(T s, const Vec3& v) {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    T dot(const Vec3& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    Vec3 cross(const Vec3& rhs) const {
        return Vec3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

    T lengthSq() const {
        return x * x + y * y + z * z;
    }

    T length() const {
        return std::sqrt(lengthSq());
    }

    Vec3 normalized() const {
        T lenSq = lengthSq();
        if (lenSq == T(0)) return Vec3();
        T invLen = T(1) / std::sqrt(lenSq);
        return Vec3(x * invLen, y * invLen, z * invLen);
    }

    bool isZero(T eps = T(1e-6)) const {
        return lengthSq() < eps * eps;
    }

    Vec3 limited(T max) const {
        T lenSq = lengthSq();
        if (lenSq > max * max) {
            T invLen = max / std::sqrt(lenSq);
            return Vec3(x * invLen, y * invLen, z * invLen);
        }
        return *this;
    }
};

}

#endif