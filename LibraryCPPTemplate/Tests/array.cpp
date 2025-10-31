#include <iostream>
#include <cassert>
#include "../array.h"

void test_array_construction() {
    std::cout << "Testing array construction..." << std::endl;

    Array<int> arr1(5);
    assert(arr1.size() == 5);

    Array<int> arr2(3, 10);
    assert(arr2.size() == 3);
    assert(arr2[0] == 10);
    assert(arr2[1] == 10);
    assert(arr2[2] == 10);

    std::cout << "Construction tests passed!" << std::endl;
}

void test_array_access() {
    std::cout << "Testing array access..." << std::endl;

    Array<int> arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 3);

    // Простая проверка исключения без лишних переменных
    try {
        (void)arr[5];
        assert(false && "Should have thrown exception");
    }
    catch (const std::out_of_range&) {
        // Expected behavior
    }

    std::cout << "Access tests passed!" << std::endl;
}

void test_array_copy() {
    std::cout << "Testing array copy..." << std::endl;

    Array<int> arr1(3);
    arr1[0] = 1;
    arr1[1] = 2;
    arr1[2] = 3;

    Array<int> arr2 = arr1;
    assert(arr2.size() == 3);
    assert(arr2[0] == 1);
    assert(arr2[1] == 2);
    assert(arr2[2] == 3);

    arr2[0] = 10;
    assert(arr1[0] == 1); // Проверка глубокого копирования

    std::cout << "Copy tests passed!" << std::endl;
}

void test_array_fill() {
    std::cout << "Testing array fill..." << std::endl;

    Array<int> arr(4);
    arr.fill(42);

    for (size_t i = 0; i < arr.size(); ++i) {
        assert(arr[i] == 42);
    }

    std::cout << "Fill tests passed!" << std::endl;
}

int main() {
    std::cout << "Starting array tests..." << std::endl;

    test_array_construction();
    test_array_access();
    test_array_copy();
    test_array_fill();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
