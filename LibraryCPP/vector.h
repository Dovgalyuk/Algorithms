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

Data vector_get(const Vector *vector, size_t index);

void vector_set(Vector *vector, size_t index, Data value);

// Retrieves current vector size
size_t vector_size(const Vector *vector);

// Changes the vector size (may increase or decrease)
void vector_resize(Vector *vector, size_t size);

#endif
