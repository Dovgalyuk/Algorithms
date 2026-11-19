#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

// Vector (dynamic array)

// Stores integer values inside
// Change it to desired type
typedef int Data;

struct Vector;

// Creates vector
Vector *vector_create();

// Deletes vector structure and internal data
void vector_delete(Vector *vector);

// Retrieves vector element with the specified index (index < size)
Data vector_get(const Vector *vector, size_t index);

// Sets vector element with the specified index (index < size)
void vector_set(Vector *vector, size_t index, Data value);

// Retrieves current vector size
size_t vector_size(const Vector *vector);

// Changes the vector size (may increase or decrease)
// New elements are zero-initialized; shrinking keeps allocated capacity.
// Growing one element at a time is O(1) amortized; a bulk resize is O(size).
void vector_resize(Vector *vector, size_t size);

#endif
