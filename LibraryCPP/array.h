#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

// Non-resizeable array
// Stores integer values inside
typedef int Data;

struct Array;

// create array
Array *array_create(size_t size);

// delete array, free memory
void array_delete(Array *arr);

// returns specified array element
Data array_get(const Array *arr, size_t index);

// sets the specified array element to the value
void array_set(Array *arr, size_t index, Data value);

// returns array size
size_t array_size(const Array *arr);

#endif
