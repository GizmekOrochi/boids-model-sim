#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#pragma once
#include <cstdlib>
#include <iostream>

namespace bd {

/**
 * @brief A simple dynamically resizing array container.
 *
 * @tparam T Type of elements stored in the array.
 *
 * This class implements a minimal dynamic array with manual memory
 * management. It provides basic functionality such as dynamic growth,
 * element insertion, indexed access, and clearing of stored elements.
 */
template <typename T>
class DynamicArray {
private:
    /** Pointer to the raw memory buffer holding the elements. */
    T* data;

    /** Current number of constructed elements in the array. */
    size_t size;

    /** Total allocated capacity of the array. */
    size_t capacity;

public:
    /**
     * @brief Constructs an empty DynamicArray.
     *
     * Initializes the array with no allocated storage.
     */
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    /**
     * @brief Destroys the DynamicArray and all contained elements.
     *
     * Calls the destructor of each stored element and frees
     * the allocated memory buffer.
     */
    ~DynamicArray() {
        for (size_t i = 0; i < size; i++) {
            data[i].~T();
        }
        std::free(data);
    }

    /**
     * @brief Returns the number of elements currently stored.
     *
     * @return The number of elements in the array.
     */
    size_t getsize() const { return size; }

    /**
     * @brief Appends an element to the end of the array.
     *
     * If the current capacity is insufficient, the internal
     * storage is grown before inserting the element.
     *
     * @param value The element to be copied into the array.
     */
    void push_back(const T& value) {
        if (size == capacity) {
            grow();
        }
        new (data + size) T(value);
        size++;
    }

    /**
    * @brief Removes the last element from the array.
    *
    * Does nothing if the array is empty.
    */
    void pop_back() {
        if (size == 0)
            return;

        size--;
        data[size].~T();
    }
    
    /**
     * @brief Appends all elements of another DynamicArray to this one.
     *
     * @param other The array whose elements will be copied and appended.
     */
    void append(const DynamicArray& other) {
        if (other.size == 0)
            return;

        // Ensure enough capacity
        if (size + other.size > capacity) {
            reserve(size + other.size);
        }

        // Copy-construct elements
        for (size_t i = 0; i < other.size; ++i) {
            new (data + size + i) T(other.data[i]);
        }

        size += other.size;
    }

    /**
     * @brief Provides mutable access to an element by index.
     *
     * @param index Index of the element.
     * @return Reference to the element at the given index.
     */
    T& operator[](size_t index) { return data[index]; }

    /**
     * @brief Provides read-only access to an element by index.
     *
     * @param index Index of the element.
     * @return Const reference to the element at the given index.
     */
    const T& operator[](size_t index) const { return data[index]; }

    /**
     * @brief Removes all elements from the array.
     *
     * Calls the destructor of each stored element but retains
     * the allocated memory for future reuse.
     */
    void clear() {
        for (size_t i = 0; i < size; ++i) {
            data[i].~T();
        }
        size = 0;
    }

private:
    /**
     * @brief Increases the capacity of the array.
     *
     * Allocates a new buffer with larger capacity, moves existing
     * elements into it using copy construction, destroys the old
     * elements, and frees the previous memory buffer.
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
            std::cout << "Error un allocation\n";
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
