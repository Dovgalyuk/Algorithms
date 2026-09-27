#pragma once

#include <cstddef>

typedef int Data;

struct Array
{
    Data* data;
    size_t size;
};

Array* array_create(size_t size);
void array_destroy(Array* arr);
size_t array_size(const Array* arr);
Data array_get(const Array* arr, size_t index);
void array_set(Array* arr, size_t index, Data value);
