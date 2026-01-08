#ifndef VEC2_HPP
#define VEC2_HPP

#pragma once
#include <cmath>

namespace bd {

/**
 * @brief Classe de vecteur 2D générique.
 *
 * @tparam T Type numérique utilisé pour les composantes du vecteur.
 *
 * Cette classe représente un vecteur à deux dimensions et fournit
 * les opérations arithmétiques vectorielles courantes, les opérations scalaires,
 * ainsi que des utilitaires géométriques de base comme la normalisation et le calcul de longueur.
 */
template <typename T>
class Vec2 {
public:
    /** Composantes X, Y du vecteur. */
    T x;
    T y;

    /**
     * @brief Construit un vecteur initialisé à zéro (0, 0).
     */
    Vec2() : x(0), y(0) {}

    /**
     * @brief Construit un vecteur avec des composantes données.
     *
     * @param newx Composante x initiale.
     * @param newy Composante y initiale.
     */
    Vec2(T newx, T newy) : x(newx), y(newy) {}

    /* Opérateurs */

    /**
     * @brief Additionne deux vecteurs.
     *
     * @param rhs Vecteur à ajouter.
     * @return Le vecteur résultat.
     */
    Vec2 operator+(const Vec2& rhs) const { return Vec2(x + rhs.x, y + rhs.y); }

    /**
     * @brief Soustrait un autre vecteur de ce vecteur.
     *
     * @param rhs Vecteur à soustraire.
     * @return Le vecteur résultat.
     */
    Vec2 operator-(const Vec2& rhs) const { return Vec2(x - rhs.x, y - rhs.y); }

    /**
     * @brief Multiplie le vecteur par un scalaire.
     *
     * @param scalar Valeur scalaire.
     * @return Le vecteur mis à l'échelle.
     */
    Vec2 operator*(T scalar) const { return Vec2(x * scalar, y * scalar); }

    /**
     * @brief Divise le vecteur par un scalaire.
     *
     * Si le scalaire est zéro, un vecteur nul est renvoyé.
     *
     * @param scalar Valeur scalaire.
     * @return Le vecteur résultat.
     */
    Vec2 operator/(T scalar) const {
        if (scalar == T(0)) return Vec2();
        return Vec2(x / scalar, y / scalar);
    }

    /**
     * @brief Comparaison d'égalité.
     *
     * @param rhs Autre vecteur.
     * @return True si les deux composantes sont égales.
     */
    bool operator==(const Vec2& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    /**
     * @brief Comparaison d'inégalité.
     *
     * @param rhs Autre vecteur.
     * @return True si une des composantes diffère.
     */
    bool operator!=(const Vec2& rhs) const {
        return !(*this == rhs);
    }

    /**
     * @brief Ajoute un autre vecteur à ce vecteur (sur place).
     *
     * @param rhs Vecteur à ajouter.
     * @return Référence vers ce vecteur modifié.
     */
    Vec2& operator+=(const Vec2& rhs) { x += rhs.x; y += rhs.y; return *this; }

    /**
     * @brief Soustrait un autre vecteur de ce vecteur (sur place).
     *
     * @param rhs Vecteur à soustraire.
     * @return Référence vers ce vecteur modifié.
     */
    Vec2& operator-=(const Vec2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

    /**
     * @brief Multiplie ce vecteur par un scalaire (sur place).
     *
     * @param s Valeur scalaire.
     * @return Référence vers ce vecteur modifié.
     */
    Vec2& operator*=(T s) { x *= s; y *= s; return *this; }

    /**
     * @brief Divise ce vecteur par un scalaire (sur place).
     *
     * Si le scalaire est zéro, le vecteur est mis à zéro.
     *
     * @param s Valeur scalaire.
     * @return Référence vers ce vecteur modifié.
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
     * @brief Multiplie un vecteur par un scalaire (ordre scalaire * vecteur).
     *
     * @param s Valeur scalaire.
     * @param v Vecteur à mettre à l'échelle.
     * @return Le vecteur mis à l'échelle.
     */
    friend Vec2 operator*(T s, const Vec2& v) {
        return Vec2(v.x * s, v.y * s);
    }

    /* Math */

    /**
     * @brief Calcule le produit scalaire (dot product) avec un autre vecteur.
     *
     * @param rhs Autre vecteur.
     * @return La valeur du produit scalaire.
     */
    T dot(const Vec2& rhs) const { return x * rhs.x + y * rhs.y; }

    /**
     * @brief Renvoie la longueur au carré du vecteur.
     *
     * @return Magnitude au carré.
     */
    T lengthSq() const { return x * x + y * y; }

    /**
     * @brief Renvoie la longueur (magnitude) du vecteur.
     *
     * @return Longueur du vecteur.
     */
    T length() const { return std::sqrt(lengthSq()); }

    /**
     * @brief Renvoie une copie normalisée du vecteur (vecteur unitaire).
     *
     * Si le vecteur a une longueur nulle, renvoie un vecteur nul.
     *
     * @return Vecteur normalisé.
     */
    Vec2 normalized() const {
        T lenSq = lengthSq();
        if (lenSq == T(0)) return Vec2();
        T invLen = T(1) / std::sqrt(lenSq);
        return Vec2(x * invLen, y * invLen);
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
     *
     * Si la longueur du vecteur dépasse le maximum donné, un vecteur mis à l'échelle
     * avec la même direction et une magnitude limitée est renvoyé.
     *
     * @param max Magnitude maximale autorisée.
     * @return Vecteur limité.
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