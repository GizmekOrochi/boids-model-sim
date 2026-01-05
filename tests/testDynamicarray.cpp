#include <iostream>
#include <cassert>
#include "../src/include/model/utils/DynamicArray.hpp"

int main() {
    bd::DynamicArray<int> arr;

    // Test push_back and size methods
    for (int i = 1; i <= 5; i++) {
        arr.push_back(i);
        assert(arr.getsize() == static_cast<size_t>(i));
        assert(arr[i - 1] == i);
    }

    // Test  operrator []
    for (size_t i = 0; i < arr.getsize(); i++) {
        assert(arr[i] == static_cast<int>(i + 1));
    }

    // Test total class with a custom type with a custom type
    struct Foo {
        int x;
        Foo(int x) : x(x) {}
        ~Foo() {}
    };

    bd::DynamicArray<Foo> Arr;

    Arr.push_back(Foo(42));
    Arr.push_back(Foo(7));

    assert(Arr.getsize() == 2);
    assert(Arr[0].x == 42);
    assert(Arr[1].x == 7);

    Arr.pop_back();
    Arr.push_back(Foo(56));
    assert(Arr[1].x == 56);

    Arr.pop_back();
    Arr.pop_back();

    bd::DynamicArray<Foo> Arr2;

    Arr.push_back(Foo(1));

    Arr.append(Arr2);
    assert(Arr[0].x == 42);
    assert(Arr2[1].x == 1);

    std::cout << "DynamicArray tests passed. The class works.\n";
    return 0;
}
