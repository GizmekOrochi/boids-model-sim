#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#pragma once
#include <cstdlib>
#include <iostream>

namespace bd {

/**
 * @brief Un conteneur de tableau à redimensionnement dynamique simple.
 *
 * @tparam T Type des éléments stockés dans le tableau.
 *
 * Cette classe implémente un tableau dynamique minimal avec une gestion manuelle
 * de la mémoire. Elle fournit des fonctionnalités de base telles que la croissance dynamique,
 * l'insertion d'éléments, l'accès indexé et le nettoyage des éléments stockés.
 */
template <typename T>
class DynamicArray {
private:
    /** Pointeur vers le buffer mémoire brut contenant les éléments. */
    T* data;

    /** Nombre actuel d'éléments construits dans le tableau. */
    size_t size;

    /** Capacité totale allouée du tableau (mémoire réservée). */
    size_t capacity;

public:
    /**
     * @brief Construit un DynamicArray vide.
     *
     * Initialise le tableau sans aucune allocation de stockage.
     */
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    /**
     * @brief Détruit le DynamicArray et tous les éléments contenus.
     *
     * Appelle le destructeur de chaque élément stocké et libère
     * le buffer mémoire alloué.
     */
    ~DynamicArray() {
        for (size_t i = 0; i < size; i++) {
            data[i].~T();
        }
        std::free(data);
    }

    /**
     * @brief Renvoie le nombre d'éléments actuellement stockés.
     *
     * @return Le nombre d'éléments dans le tableau.
     */
    size_t getsize() const { return size; }

    /**
     * @brief Ajoute un élément à la fin du tableau.
     *
     * Si la capacité actuelle est insuffisante, le stockage interne
     * est agrandi avant d'insérer l'élément.
     *
     * @param value L'élément à copier dans le tableau.
     */
    void push_back(const T& value) {
        if (size == capacity) {
            grow();
        }
        new (data + size) T(value);
        size++;
    }

    /**
    * @brief Retire le dernier élément du tableau.
    *
    * Ne fait rien si le tableau est vide.
    */
    void pop_back() {
        if (size == 0)
            return;

        size--;
        data[size].~T();
    }

    /**
     * @brief Retire l'élément à l'index donné.
     *
     * Déale tous les éléments suivants d'une position vers la gauche.
     *
     * @param index Index de l'élément à retirer.
     */
    void erase(size_t index) {
        if (index >= size)
            return;

        data[index].~T();

        for (size_t i = index; i < size - 1; ++i) {
            new (data + i) T(data[i + 1]);
            data[i + 1].~T();
        }
        size--;
    }

    /**
     * @brief Fournit un accès modifiable à un élément par index.
     *
     * @param index Index de l'élément.
     * @return Référence vers l'élément à l'index donné.
     */
    T& operator[](size_t index) { return data[index]; }

    /**
     * @brief Fournit un accès en lecture seule à un élément par index.
     *
     * @param index Index de l'élément.
     * @return Référence constante vers l'élément à l'index donné.
     */
    const T& operator[](size_t index) const { return data[index]; }

    /**
     * @brief Retire tous les éléments du tableau.
     *
     * Appelle le destructeur de chaque élément stocké mais conserve
     * la mémoire allouée pour une réutilisation future.
     */
    void clear() {
        for (size_t i = 0; i < size; ++i) {
            data[i].~T();
        }
        size = 0;
    }

private:
    /**
     * @brief Augmente la capacité du tableau.
     *
     * Alloue un nouveau buffer avec une capacité plus grande, déplace les
     * éléments existants dedans via le constructeur de copie, détruit les anciens
     * éléments et libère l'ancien buffer mémoire.
     */
    void grow() {
        // nouvelle capacité: 1 ou * 2
        size_t new_capacity;

        if (capacity == 0) {
            new_capacity = 1;
        } else {
            new_capacity = capacity * 2;
        }

        // alloue
        T* new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T)));
        if (!new_data) {
            std::cout << "Erreur d'allocation\n";
            return;
        }

        // déplace les anciens objets
        for (size_t i = 0; i < size; i++) {
            new (new_data + i) T(data[i]);
            data[i].~T();
        }
        std::free(data);

        // met à jour
        data = new_data;
        capacity = new_capacity;
    }
};

}

#endif // DYNAMICARRAY_HPP