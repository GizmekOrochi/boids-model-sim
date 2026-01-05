#ifndef VEC2_HPP
#define VEC2_HPP

#pragma once
#include <cmath>

namespace bd {

/**
 * @brief A generic 2D vector class.
 *
 * @tparam T Numeric type used for vector components.
 *
 * This class represents a two-dimensional vector and provides
 * common vector arithmetic operations, scalar operations, and
 * basic geometric utilities such as normalization and length
 * computation.
 */
template <typename T>
class Vec2 {
public:
    /** X, Y component of the vector. */
    T x;
    T y;

    /**
     * @brief Constructs a zero-initialized vector.
     */
    Vec2() : x(0), y(0) {}

    /**
     * @brief Constructs a vector with given components.
     *
     * @param newx Initial x component.
     * @param newy Initial y component.
     */
    Vec2(T newx, T newy) : x(newx), y(newy) {}

    /* Operators */

    /**
     * @brief Adds two vectors.
     *
     * @param rhs Vector to add.
     * @return Resulting vector.
     */
    Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }

    /**
     * @brief Subtracts another vector from this vector.
     *
     * @param rhs Vector to subtract.
     * @return Resulting vector.
     */
    Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }

    /**
     * @brief Multiplies the vector by a scalar.
     *
     * @param scalar Scalar value.
     * @return Scaled vector.
     */
    Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }

    /**
     * @brief Divides the vector by a scalar.
     *
     * If the scalar is zero, a zero vector is returned.
     *
     * @param scalar Scalar value.
     * @return Resulting vector.
     */
    Vec2 operator/(T scalar) const {
        if (scalar == T(0)) return Vec2();
        return Vec2(x / scalar, y / scalar);
    }
    
    /**
     * @brief Equality comparison.
     *
     * @param rhs Other vector.
     * @return True if both components are equal.
     */
    bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    /**
     * @brief Inequality comparison.
     *
     * @param rhs Other vector.
     * @return True if any component differs.
     */
    bool operator!=(const Vec2& rhs) const {
        return !(*this == rhs);
    }

    /**
     * @brief Adds another vector to this vector in place.
     *
     * @param rhs Vector to add.
     * @return Reference to this vector.
     */
    Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }

    /**
     * @brief Subtracts another vector from this vector in place.
     *
     * @param rhs Vector to subtract.
     * @return Reference to this vector.
     */
    Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    /**
     * @brief Multiplies this vector by a scalar in place.
     *
     * @param s Scalar value.
     * @return Reference to this vector.
     */
    Vec2& operator*=(T s) { x *= s; y *= s; return *this; }

    /**
     * @brief Divides this vector by a scalar in place.
     *
     * If the scalar is zero, the vector is set to zero.
     *
     * @param s Scalar value.
     * @return Reference to this vector.
     */
    Vec2& operator/=(T s) {
        if (s != T(0)) {
            x /= s;
            y /= s;
        } else {
            x = y = T(0);
        }
        return *this;
    }

    /**
     * @brief Multiplies a vector by a scalar (scalar first).
     *
     * @param s Scalar value.
     * @param v Vector to scale.
     * @return Scaled vector.
     */
    friend Vec2 operator*(T s, const Vec2& v) {
        return Vec2(v.x * s, v.y * s);
    }

    /* Math */

    /**
     * @brief Computes the dot product with another vector.
     *
     * @param rhs Other vector.
     * @return Dot product value.
     */
    T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }

    /**
     * @brief Returns the squared length of the vector.
     *
     * @return Squared magnitude.
     */
    T lengthSq() const { return x * x + y * y; }

    /**
     * @brief Returns the length (magnitude) of the vector.
     *
     * @return Vector length.
     */
    T length() const { return std::sqrt(lengthSq()); }

    /**
     * @brief Returns a normalized copy of the vector.
     *
     * If the vector has zero length, a zero vector is returned.
     *
     * @return Normalized vector.
     */
    Vec2 normalized() const {
        T lenSq = lengthSq();
        if (lenSq == T(0)) return Vec2();
        T invLen = T(1) / std::sqrt(lenSq);
        return Vec2(x * invLen, y * invLen);
    }

    /**
     * @brief Checks whether the vector is approximately zero.
     *
     * @param eps Tolerance value.
     * @return True if the vector magnitude is below the tolerance.
     */
    bool isZero(T eps = T(1e-6)) const {
        return lengthSq() < eps * eps;
    }

    /**
     * @brief Limits the vector magnitude to a maximum value.
     *
     * If the vector length exceeds the given maximum, a scaled
     * vector with the same direction and limited magnitude is returned.
     *
     * @param max Maximum allowed magnitude.
     * @return Limited vector.
     */
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
