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

// Retrieves vector element with the specified index
// Throws std::out_of_range when index >= vector_size(vector)
Data vector_get(const Vector *vector, size_t index);

// Sets vector element with the specified index
// Throws std::out_of_range when index >= vector_size(vector)
void vector_set(Vector *vector, size_t index, Data value);

// Retrieves current vector size
size_t vector_size(const Vector *vector);

// Changes the vector size (may increase or decrease)
// Growing by one is O(1) amortized; new elements are initialized to zero.
// Shrinking keeps allocated capacity.
void vector_resize(Vector *vector, size_t size);

#endif
