#include "array.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

// Тест создания массива, проверки размера и удаления
void test_create_size_delete() {
    // Обычный массив
    Array* arr1 = array_create(10);
    assert(arr1 != nullptr);
    assert(array_size(arr1) == 10);
    array_delete(&arr1);
    assert(arr1 == nullptr); // Указатель должен обнулиться

    // Пустой массив (размер 0)
    Array* arr2 = array_create(0);
    assert(arr2 != nullptr);
    assert(array_size(arr2) == 0);
    array_delete(&arr2);
    assert(arr2 == nullptr);

    // Безопасное удаление nullptr
    Array* arr3 = nullptr;
    array_delete(&arr3); // Не должно вызвать падение
    assert(arr3 == nullptr);
    
    std::cout << "[PASS] test_create_size_delete\n";
}

// Тест инициализации массива нулями
void test_initialization() {
    Array* arr = array_create(5);
    for (std::size_t i = 0; i < 5; ++i) {
        assert(array_get(arr, i) == 0); // new int[size]{} инициализирует нулями
    }
    array_delete(&arr);
    std::cout << "[PASS] test_initialization\n";
}

// Тест записи и чтения данных
void test_set_and_get() {
    Array* arr = array_create(3);
    array_set(arr, 0, 10);
    array_set(arr, 1, 20);
    array_set(arr, 2, 30);
    
    assert(array_get(arr, 0) == 10);
    assert(array_get(arr, 1) == 20);
    assert(array_get(arr, 2) == 30);
    
    array_delete(&arr);
    std::cout << "[PASS] test_set_and_get\n";
}

// Тест обработки исключений (ошибок)
void test_exceptions() {
    // 1. Передача nullptr в функции
    try {
        array_size(nullptr);
        assert(false); // Исключение должно было выпасть
    } catch (const std::invalid_argument&) { /* OK */ }

    try {
        array_set(nullptr, 0, 0);
        assert(false);
    } catch (const std::invalid_argument&) { /* OK */ }

    try {
        array_get(nullptr, 0);
        assert(false);
    } catch (const std::invalid_argument&) { /* OK */ }

    // 2. Выход за границы массива (out_of_range)
    Array* arr = array_create(5);
    
    try {
        array_set(arr, 5, 100); // Индекс 5 при размере 5 - это ошибка
        assert(false);
    } catch (const std::out_of_range&) { /* OK */ }

    try {
        array_get(arr, 10); 
        assert(false);
    } catch (const std::out_of_range&) { /* OK */ }
    
    array_delete(&arr);
    std::cout << "[PASS] test_exceptions\n";
}

int main() {
    std::cout << "Running array.cpp tests...\n";
    test_create_size_delete();
    test_initialization();
    test_set_and_get();
    test_exceptions();
    std::cout << "All tests passed successfully!\n";
    return 0;
}