#include "array.h"

struct Array
{
    Data* array; // указат на массив
    size_t size; // размер массива

    Array(size_t size) {
        this->size = size;
        array = new Data[size]; // объявил массив
    }

    ~Array() {
        delete[] array;
    }
};

// создать массив
Array *array_create(size_t size)
{
    return new Array(size);
}

// удалить массив, освободить память
void array_delete(Array *arr)
{
    delete arr;
}

// возвращает указанный элемент массива
Data array_get(const Array *arr, size_t index)
{
    return arr->array[index];
}

// устанавливает указанный элемент массива в значение
void array_set(Array *arr, size_t index, Data value)
{
    arr->array[index] = value;
}

// возвращает размер массива
size_t array_size(const Array *arr)
{
    return arr->size;
}