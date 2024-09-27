#include "array.h"


// Структура массива
struct Array {
    Data* elements;
    size_t size;
};

// Создание массива
Array* array_create(size_t size)
{
    Array* arr = new Array;
    arr->elements = new Data[size];
    arr->size = size;
    if (size == 0) {
        return nullptr;
    }
    return new Array;
}

// Удалить массив, освободить память
void array_delete(Array* arr)
{
    delete[] arr->elements;
    delete arr;
}

// Возвращение указанного элемента массива
Data array_get(const Array* arr, size_t index) {
    return arr->elements[index];
}

// Установить значение указанного элемента в массиве
void array_set(Array* arr, size_t index, Data value) {
    arr->elements[index] = value;
}

// Вернуть размер массива
size_t array_size(const Array* arr)
{
    return arr->size;
}
