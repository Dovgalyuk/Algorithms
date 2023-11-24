#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

typedef int Data;

struct Array
{
	Data* data;
	size_t size;
};

Array* array_create(size_t size);
void array_delete(Array* arr);
Data array_get(const Array* arr, size_t index);
void array_set(Array* arr, size_t index, Data value);
size_t array_size(const Array* arr);

#endif // ARRAY_H
