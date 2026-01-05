#ifndef VEC3_HPP
#define VEC3_HPP

#pragma once
#include <cmath>

namespace bd {

/**
 * @brief A generic 3D vector class.
 *
 * @tparam T Numeric type used for vector components.
 *
 * This class represents a three-dimensional vector and provides
 * common vector arithmetic operations, scalar operations, and
 * basic geometric utilities such as normalization and length
 * computation.
 */
template <typename T>
class Vec3 {
public:
    /** X, Y, Z components of the vector. */
    T x;
    T y;
    T z;

    /**
     * @brief Constructs a zero-initialized vector.
     */
    Vec3() : x(0), y(0), z(0) {}

    /**
     * @brief Constructs a vector with given components.
     *
     * @param newx Initial x component.
     * @param newy Initial y component.
     * @param newz Initial z component.
     */
    Vec3(T newx, T newy, T newz) : x(newx), y(newy), z(newz) {}

    /* Operators */

    /**
     * @brief Adds two vectors.
     */
    Vec3 operator+(const Vec3& rhs) const {
        return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    /**
     * @brief Subtracts another vector from this vector.
     */
    Vec3 operator-(const Vec3& rhs) const {
        return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    /**
     * @brief Multiplies the vector by a scalar.
     */
    Vec3 operator*(T scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Divides the vector by a scalar.
     *
     * If the scalar is zero, a zero vector is returned.
     */
    Vec3 operator/(T scalar) const {
        if (scalar == T(0)) return Vec3();
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    /**
     * @brief Equality comparison.
     */
    bool operator==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    /**
     * @brief Inequality comparison.
     */
    bool operator!=(const Vec3& rhs) const {
        return !(*this == rhs);
    }

    /**
     * @brief Adds another vector to this vector in place.
     */
    Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }

    /**
     * @brief Subtracts another vector from this vector in place.
     */
    Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x; y -= rhs.y; z -= rhs.z;
        return *this;
    }

    /**
     * @brief Multiplies this vector by a scalar in place.
     */
    Vec3& operator*=(T s) {
        x *= s; y *= s; z *= s;
        return *this;
    }

    /**
     * @brief Divides this vector by a scalar in place.
     *
     * If the scalar is zero, the vector is set to zero.
     */
    Vec3& operator/=(T s) {
        if (s != T(0)) {
            x /= s; y /= s; z /= s;
        } else {
            x = y = z = T(0);
        }
        return *this;
    }

    /**
     * @brief Multiplies a vector by a scalar (scalar first).
     */
    friend Vec3 operator*(T s, const Vec3& v) {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    /* Math */

    /**
     * @brief Computes the dot product with another vector.
     */
    T dot(const Vec3& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    /**
     * @brief Computes the cross product with another vector.
     */
    Vec3 cross(const Vec3& rhs) const {
        return Vec3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

    /**
     * @brief Returns the squared length of the vector.
     */
    T lengthSq() const {
        return x * x + y * y + z * z;
    }

    /**
     * @brief Returns the length (magnitude) of the vector.
     */
    T length() const {
        return std::sqrt(lengthSq());
    }

    /**
     * @brief Returns a normalized copy of the vector.
     *
     * If the vector has zero length, a zero vector is returned.
     */
    Vec3 normalized() const {
        T lenSq = lengthSq();
        if (lenSq == T(0)) return Vec3();
        T invLen = T(1) / std::sqrt(lenSq);
        return Vec3(x * invLen, y * invLen, z * invLen);
    }

    /**
     * @brief Checks whether the vector is approximately zero.
     *
     * @param eps Tolerance value.
     */
    bool isZero(T eps = T(1e-6)) const {
        return lengthSq() < eps * eps;
    }

    /**
     * @brief Limits the vector magnitude to a maximum value.
     */
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
