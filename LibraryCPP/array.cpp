#include "array.h"

struct Array
{
    Data* data;
    size_t size;
};

// Создание массива
Array* array_create(size_t size)
{
    Array* arr = new Array();

    arr->data = new Data[size];
    arr->size = size;

    return arr;
}

// Удаление массива
void array_delete(Array* arr)
{
    if (arr == nullptr)
    {
        return;
    }

    delete[] arr->data;
    delete arr;
}

// Получение элемента
Data array_get(const Array* arr, size_t index)
{
    if (arr == nullptr || arr->data == nullptr || index >= arr->size)
    {
        return 0;
    }

    return arr->data[index];
}

// Установка элемента
void array_set(Array* arr, size_t index, Data value)
{
    if (arr == nullptr || arr->data == nullptr || index >= arr->size)
    {
        return;
    }

    arr->data[index] = value;
}

// Получение размера
size_t array_size(const Array* arr)
{
    if (arr == nullptr)
    {
        return 0;
    }

    return arr->size;
}