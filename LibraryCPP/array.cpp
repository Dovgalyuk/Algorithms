#include "array.h" 
#include <stdexcept> 

struct Array {
    Data* array; 
    size_t size; 
};


Array* array_create(size_t size) {
    if (size == 0) { 
        return nullptr; 
    }
    Array* arr = new Array; 
    arr->size = size; 
    arr->array = new Data[size]; 
    return arr; 
}

// Функция для удаления массива и освобождения памяти
void array_delete(Array* arr) {
    if (arr) { 
        delete[] arr->array;
        delete arr; 
    }
}

// Функция для получения элемента массива по индексу
Data array_get(const Array* arr, size_t index) {
    if (!arr || index >= arr->size) { 
        throw std::out_of_range("Index out of bounds"); 
    return arr->array[index]; 
}

// Функция для установки значения элемента массива по индексу
void array_set(Array* arr, size_t index, Data value) {
    if (!arr || index >= arr->size) { 
        throw std::out_of_range("Index out of bounds"); 
    }
    arr->array[index] = value; 
}

// Функция для получения размера массива
size_t array_size(const Array* arr) {
    if (!arr) { 
        return 0; 
    }
    return arr->size; 
}
