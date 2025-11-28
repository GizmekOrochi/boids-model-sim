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
            grow(value); 
        }
        new (data + size) T(value);
        size++;
    }

    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }

private:
    void grow(const T& value) {
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
