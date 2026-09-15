
#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

// Non-resizeable array.
// Stores integer values inside.
typedef int Data;

struct Array;

// Create array with fixed size.
Array* array_create(size_t size);

// Delete array and free memory.
void array_delete(Array** arr);

// Returns specified array element.
Data array_get(const Array* arr, size_t index);

// Sets the specified array element to the value.
void array_set(Array* arr, size_t index, Data value);

// Returns array size.
size_t array_size(const Array* arr);

#endif

