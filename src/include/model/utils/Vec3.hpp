#ifndef VEC3_HPP
#define VEC3_HPP

#pragma once
#include <cmath>

namespace bd {

/**
 * @brief Classe de vecteur 3D générique.
 *
 * @tparam T Type numérique utilisé pour les composantes du vecteur (float, double, etc.).
 *
 * Cette classe représente un vecteur à trois dimensions et fournit
 * les opérations arithmétiques vectorielles courantes, les opérations scalaires,
 * ainsi que des utilitaires géométriques de base comme la normalisation et le calcul de longueur.
 */
template <typename T>
class Vec3 {
public:
    /** Composantes X, Y, Z du vecteur. */
    T x;
    T y;
    T z;

    /**
     * @brief Construit un vecteur initialisé à zéro (0, 0, 0).
     */
    Vec3() : x(0), y(0), z(0) {}

    /**
     * @brief Construit un vecteur avec des composantes données.
     *
     * @param newx Composante x initiale.
     * @param newy Composante y initiale.
     * @param newz Composante z initiale.
     */
    Vec3(T newx, T newy, T newz) : x(newx), y(newy), z(newz) {}

    /* Opérateurs */

    /**
     * @brief Additionne deux vecteurs.
     * * @param rhs Vecteur à ajouter.
     * @return Le vecteur résultat.
     */
    Vec3 operator+(const Vec3& rhs) const {
        return Vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    /**
     * @brief Soustrait un autre vecteur de ce vecteur.
     * * @param rhs Vecteur à soustraire.
     * @return Le vecteur résultat.
     */
    Vec3 operator-(const Vec3& rhs) const {
        return Vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    /**
     * @brief Multiplie le vecteur par un scalaire.
     * * @param scalar Valeur scalaire.
     * @return Le vecteur mis à l'échelle.
     */
    Vec3 operator*(T scalar) const {
        return Vec3(x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Divise le vecteur par un scalaire.
     *
     * Si le scalaire est zéro, un vecteur nul est renvoyé.
     * * @param scalar Valeur scalaire.
     * @return Le vecteur résultat.
     */
    Vec3 operator/(T scalar) const {
        if (scalar == T(0)) return Vec3();
        return Vec3(x / scalar, y / scalar, z / scalar);
    }

    /**
     * @brief Comparaison d'égalité.
     * * @param rhs Autre vecteur.
     * @return True si toutes les composantes sont égales.
     */
    bool operator==(const Vec3& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    /**
     * @brief Comparaison d'inégalité.
     * * @param rhs Autre vecteur.
     * @return True si au moins une composante diffère.
     */
    bool operator!=(const Vec3& rhs) const {
        return !(*this == rhs);
    }

    /**
     * @brief Ajoute un autre vecteur à ce vecteur (sur place).
     * * @param rhs Vecteur à ajouter.
     * @return Référence vers ce vecteur modifié.
     */
    Vec3& operator+=(const Vec3& rhs) {
        x += rhs.x; y += rhs.y; z += rhs.z;
        return *this;
    }

    /**
     * @brief Soustrait un autre vecteur de ce vecteur (sur place).
     * * @param rhs Vecteur à soustraire.
     * @return Référence vers ce vecteur modifié.
     */
    Vec3& operator-=(const Vec3& rhs) {
        x -= rhs.x; y -= rhs.y; z -= rhs.z;
        return *this;
    }

    /**
     * @brief Multiplie ce vecteur par un scalaire (sur place).
     * * @param s Valeur scalaire.
     * @return Référence vers ce vecteur modifié.
     */
    Vec3& operator*=(T s) {
        x *= s; y *= s; z *= s;
        return *this;
    }

    /**
     * @brief Divise ce vecteur par un scalaire (sur place).
     *
     * Si le scalaire est zéro, le vecteur est mis à zéro.
     * * @param s Valeur scalaire.
     * @return Référence vers ce vecteur modifié.
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
     * @brief Multiplie un vecteur par un scalaire (ordre scalaire * vecteur).
     * * @param s Valeur scalaire.
     * @param v Vecteur à mettre à l'échelle.
     * @return Le vecteur mis à l'échelle.
     */
    friend Vec3 operator*(T s, const Vec3& v) {
        return Vec3(v.x * s, v.y * s, v.z * s);
    }

    /* Math */

    /**
     * @brief Calcule le produit scalaire (dot product) avec un autre vecteur.
     * * @param rhs Autre vecteur.
     * @return La valeur du produit scalaire.
     */
    T dot(const Vec3& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    /**
     * @brief Calcule le produit vectoriel (cross product) avec un autre vecteur.
     * * @param rhs Autre vecteur.
     * @return Le vecteur résultant (perpendiculaire aux deux autres).
     */
    Vec3 cross(const Vec3& rhs) const {
        return Vec3(
            y * rhs.z - z * rhs.y,
            z * rhs.x - x * rhs.z,
            x * rhs.y - y * rhs.x
        );
    }

    /**
     * @brief Renvoie la longueur au carré du vecteur.
     * * @return Magnitude au carré.
     */
    T lengthSq() const {
        return x * x + y * y + z * z;
    }

    /**
     * @brief Renvoie la longueur (magnitude) du vecteur.
     * * @return Longueur du vecteur.
     */
    T length() const {
        return std::sqrt(lengthSq());
    }

    /**
     * @brief Renvoie une copie normalisée du vecteur (vecteur unitaire).
     *
     * Si le vecteur a une longueur nulle, renvoie un vecteur nul.
     * * @return Vecteur normalisé.
     */
    Vec3 normalized() const {
        T lenSq = lengthSq();
        if (lenSq == T(0)) return Vec3();
        T invLen = T(1) / std::sqrt(lenSq);
        return Vec3(x * invLen, y * invLen, z * invLen);
    }

    /**
     * @brief Vérifie si le vecteur est approximativement nul.
     *
     * @param eps Valeur de tolérance (epsilon).
     * @return True si la magnitude du vecteur est inférieure à la tolérance.
     */
    bool isZero(T eps = T(1e-6)) const {
        return lengthSq() < eps * eps;
    }

    /**
     * @brief Limite la magnitude du vecteur à une valeur maximale.
     * * @param max Magnitude maximale autorisée.
     * @return Vecteur tronqué à la longueur maximale si nécessaire.
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