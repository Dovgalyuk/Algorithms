#include <iostream>
#include <cmath>
#include "array.h"
#include "task1.h"
#include "task2.h"

int main() {
    int passed = 0, failed = 0;

    Array *arr = array_create(5);

    array_set(arr, 0, 4.5);
    array_set(arr, 1, 7.3);
    array_set(arr, 2, 12.4);
    array_set(arr, 3, 9.2);
    array_set(arr, 4, 3.4);

    double result = task1(arr);

    if (std::abs(result - 1.187) < 0.01) {
        std::cout << "Test 1 task1 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 1 task1 failed" << '\n';
        failed++;
    }

    array_set(arr, 0, 0);
    array_set(arr, 1, 0);
    array_set(arr, 2, 0);
    array_set(arr, 3, 0);
    array_set(arr, 4, 0);

    result = task1(arr);

    if (result == 0.0) {
        std::cout << "Test 2 task1 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 2 task1 failed" << '\n';
        failed++;
    }

    array_delete(arr);

    Array *arr1 = array_create(1);
    array_set(arr1, 0, 4);

    result = task1(arr1);

    if (std::abs(result - 4) < 0.01) {
        std::cout << "Test 3 task1 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 3 task1 failed" << '\n';
        failed++;
    }

    array_delete(arr1);

    Array *arr2 = array_create(3);

    array_set(arr2, 0, 0);
    array_set(arr2, 1, 2.3);
    array_set(arr2, 2, 0.3);

    result = task1(arr2);

    if (result == 0.0) {
        std::cout << "Test 4 task1 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 4 task1 failed" << '\n';
        failed++;
    }

    array_delete(arr2);

    size_t res = 0;
    Array *arr3 = array_create(7);

    array_set(arr3, 0, 1);
    array_set(arr3, 1, 2);
    array_set(arr3, 2, 3);
    array_set(arr3, 3, 5);
    array_set(arr3, 4, 10);
    array_set(arr3, 5, 20);
    array_set(arr3, 6, 40);

    res = task2(arr3);

    if (res == 2) {
        std::cout << "Test 1 task2 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 1 task2 failed" << '\n';
        failed++;
    }

    array_set(arr3, 0, 20);
    array_set(arr3, 1, 20);
    array_set(arr3, 2, 20);
    array_set(arr3, 3, 20);
    array_set(arr3, 4, 20);
    array_set(arr3, 5, 1);
    array_set(arr3, 6, 1);

    res = task2(arr3);

    if (res == 0) {
        std::cout << "Test 2 task2 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 2 task2 failed" << '\n';
        failed++;
    }

    array_set(arr3, 0, -10);
    array_set(arr3, 1, -40);
    array_set(arr3, 2, -1);
    array_set(arr3, 3, -2);
    array_set(arr3, 4, -4);
    array_set(arr3, 5, -3);
    array_set(arr3, 6, -7);

    res = task2(arr3);

    if (res == 2) {
        std::cout << "Test 3 task2 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 3 task2 failed" << '\n';
        failed++;
    }

    array_delete(arr3);

    Array *arr4 = array_create(10);

    array_set(arr4, 0, -10);
    array_set(arr4, 1, -5);
    array_set(arr4, 2, -3);
    array_set(arr4, 3, -7);
    array_set(arr4, 4, -2);
    array_set(arr4, 5, 10);
    array_set(arr4, 6, 15);
    array_set(arr4, 7, -4);
    array_set(arr4, 8, 8);
    array_set(arr4, 9, 12);

    res = task2(arr4);

    if (res == 5) {
        std::cout << "Test 4 task2 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 4 task2 failed" << '\n';
        failed++;
    }

    array_delete(arr4);

    Array *arr5 = array_create(5);

    array_set(arr5, 0, 1);
    array_set(arr5, 1, 2);
    array_set(arr5, 2, 3);
    array_set(arr5, 3, 4);
    array_set(arr5, 4, 5);

    res = task2(arr5);

    if (res == 0) {
        std::cout << "Test 5 task2 passed" << '\n';
        passed++;
    } else {
        std::cout << "Test 5 task2 failed" << '\n';
        failed++;
    }

    array_delete(arr5);

    std::cout << "Тестов пройдено: " << passed << "\n";
    std::cout << "Тестов не пройдено: " << failed << "\n";

    if (failed == 0) {
        return 0;
    } else {
        return 1;
    }

}