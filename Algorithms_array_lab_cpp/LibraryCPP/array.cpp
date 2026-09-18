#include "array.h"

struct Array
{
    Data* data;     // Указатель на массив данных
    size_t size;    // Реальный размер массива
};

// Создание массива
Array *array_create(size_t size)
{
    Array* arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    return arr;
}

// Удаление массива и освобождение памяти
void array_delete(Array *arr)
{
    delete[] arr->data;
    delete arr;
}

// Возврат элемента по индексу
Data array_get(const Array *arr, size_t index)
{
    if (index < arr->size) {
        return arr->data[index];
    }
    return (Data)0; // Возвращаем 0, если индекс вне границ
}

// Установка значения элемента по индексу
void array_set(Array *arr, size_t index, Data value)
{
    if (index < arr->size) {
        arr->data[index] = value;
    }
}

// Возврат реального размера массива
size_t array_size(const Array *arr)
{
    return arr->size;
}