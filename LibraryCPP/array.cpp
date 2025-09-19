/*#include "array.h"

struct Array
{
};

// create array
Array *array_create(size_t size)
{
    return new Array;
}

// delete array, free memory
void array_delete(Array *arr)
{
    delete arr;
}

// returns specified array element
Data array_get(const Array *arr, size_t index)
{
    return (Data)0;
}

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value)
{
}

// returns array size
size_t array_size(const Array *arr)
{
    return 0;
}*/



#include "array.h"

Array* array_create(size_t size) {
    if (size <= 0) throw std::invalid_argument("Size >0");
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size]; // Выделение памяти
    for (size_t i = 0; i < size; i++) arr->data[i] = 0; // Заполнение нулями
    return arr;
}

void array_delete(Array* arr) {
    delete[] arr->data; // Очистка массива
    delete arr; // Очистка структуры
}

size_t array_size(const Array* arr) {
    return arr->size;
}

Data array_get(const Array* arr, size_t index) {
    if (index >= arr->size) throw std::out_of_range("Index wrong");
    return arr->data[index];
}

void array_set(Array* arr, size_t index, Data value) {
    if (index >= arr->size) throw std::out_of_range("Index wrong");
    arr->data[index] = value;
}