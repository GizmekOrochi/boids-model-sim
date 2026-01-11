#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#pragma once
#include <cstdlib>
#include <iostream>

namespace bd {

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}
    ~DynamicArray() {
        for (size_t i = 0; i < size; i++) {
            data[i].~T();
        }
        std::free(data);
    }

    size_t getsize() const { return size; }

    void push_back(const T& value) {
        if (size == capacity) {
            grow();
        }
        new (data + size) T(value);
        size++;
    }

    void pop_back() {
        if (size == 0)
            return;

        size--;
        data[size].~T();
    }

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

    T& operator[](size_t index) { return data[index]; }

    const T& operator[](size_t index) const { return data[index]; }

    void clear() {
        for (size_t i = 0; i < size; ++i) {
            data[i].~T();
        }
        size = 0;
    }

private:

    void grow() {
        size_t new_capacity;

        if (capacity == 0) {
            new_capacity = 1;
        } else {
            new_capacity = capacity * 2;
        }

        T* new_data = static_cast<T*>(std::malloc(new_capacity * sizeof(T)));
        if (!new_data) {
            std::cout << "Erreur d'allocation\n";
            return;
        }

        for (size_t i = 0; i < size; i++) {
            new (new_data + i) T(data[i]);
            data[i].~T();
        }
        std::free(data);

        data = new_data;
        capacity = new_capacity;
    }
};

} // namespace

#endif // DYNAMICARRAY_HPP