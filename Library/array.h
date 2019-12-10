#ifndef ARRAY_H
#define ARRAY_H

typedef int Data;

struct Array;

Array *array_create(size_t size);

void array_delete(Array *arr);

Data array_get(const Array *arr, size_t index);

void array_set(Array *arr, size_t index, Data value);

size_t array_size(const Array *arr);

#endif
