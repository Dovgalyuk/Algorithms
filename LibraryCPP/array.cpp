#include "array.h"
#include <iostream>
#include <cstdlib>

struct Array {
    Data *data;
    size_t capacity;
};

// create array
Array* array_create(size_t initCapacity){
    Array* arr = new Array;
    arr->data = new Data[initCapacity];
    arr->capacity = initCapacity;
    return arr;
}

// delete array, free memory
void array_delete(Array* arr) {
    delete[] arr->data; // Освобождаем память под массив
    delete arr;
}

// returns specified array element
int array_get(const Array* arr, size_t index) {
    if (index < arr->capacity) {
        return arr->data[index]; // Возвращаем элемент
    } else {
        std::cerr << "Index out of bounds\n"; // Сообщение об ошибке
        exit(EXIT_FAILURE);
    }
}

// sets the specified array element to the value
void array_set(Array* arr, size_t index, Data value) {
    if (index < arr->capacity) {
        arr->data[index] = value; // Заменяем элемент
    } else {
        std::cerr << "Index out of bounds\n"; // Сообщение об ошибке
    }
}

// returns array size
size_t array_size(const Array* arr) {
    return arr->capacity;
}