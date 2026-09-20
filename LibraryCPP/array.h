#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

// Тип данных, хранящихся в массиве
typedef int Data;

struct Array;

// Создание массива фиксированного размера
Array* array_create(size_t size);

// Удаление массива и освобождение памяти
void array_delete(Array* arr);

// Получение элемента массива по индексу
Data array_get(const Array* arr, size_t index);

// Изменение элемента массива
void array_set(Array* arr, size_t index, Data value);

// Получение размера массива
size_t array_size(const Array* arr);

#endif