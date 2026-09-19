#include "array.h"

// Структура массива: хранится указатель на данные и размер
struct Array
{
    Data *data;   // указатель на область памяти с элементами
    size_t size;  // количество элементов в массиве
};

// Создаётся массив заданного размера.
// Выделяется память под структуру и под элементы.
Array *array_create(size_t size)
{
    Array *arr = new Array;
    arr->size = size;
    arr->data = new Data[size];
    return arr;
}

// Удаляется массив и освобождается вся выделенная память.
void array_delete(Array *arr)
{
    delete[] arr->data;
    delete arr;
}

// Возвращается элемент массива по указанному индексу.
Data array_get(const Array *arr, size_t index)
{
    return arr->data[index];
}

// Устанавливается значение элемента массива по указанному индексу.
void array_set(Array *arr, size_t index, Data value)
{
    arr->data[index] = value;
}

// Возвращается размер массива.
size_t array_size(const Array *arr)
{
    return arr->size;
}
