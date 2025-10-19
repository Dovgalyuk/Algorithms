#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

typedef int Data;

Data* array_create(size_t size);

void array_delete(Data* arr);

Data array_get(const Data* arr, size_t index);

void array_set(Data* arr, size_t index, Data value);

size_t array_size(const Data* arr, size_t size);

#endif
