#include "array.h"

// Non-resizeable array
// Stores integer values inside
struct Array{
    Data *data;
    size_t size;
};

// create array
Array *array_create(size_t size) {
    if (size == 0) //Проверка на размер
        return nullptr;
    Array *arr = new Array;
    if (!arr) //Проверка на создание массива
        return nullptr;
    arr->data = new Data[size];
    arr->size = size;
    if (!arr->data) { //Проверка на создание даты
        delete arr;
        return nullptr;
    }
    return arr;
};

// delete array, free memory
void array_delete(Array *arr){
    delete[] arr->data;
    delete arr;
};

// returns specified array element
Data array_get(const Array *arr, size_t index) {
    if (!arr) return; // Проверка на наличия массива
    if (index >= arr->size) return; //Проверка на индекс
    return arr->data[index];
};

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value) {
    if (!arr) return; // Проверка на наличия массива
    if (index >= arr->size) return; //Проверка на индекс
    arr->data[index] = value;
};

// returns array size
size_t array_size(const Array *arr) {
    if (arr->size == 0) return 0;
    return arr->size;
};