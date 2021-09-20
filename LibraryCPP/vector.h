#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>

// Vector (dynamic array)
// Stores integer values inside
typedef int Data;

struct Vector;

void vector_data_copy(Vector* vector, Data* new_data, size_t size, size_t offset_old_data = 0, size_t offset_new_data = 0);

void vector_set_data(Vector* vector, Data* new_data, size_t size);

void vector_expand_data(Vector* vector, size_t size);

// Creates vector
Vector *vector_create();

// Deletes vector structure and internal data
void vector_delete(Vector *vector);

// Retrieves vector element with the specified index
Data vector_get(const Vector *vector, size_t index);

// Sets vector element with the specified index
void vector_set(Vector *vector, size_t index, Data value);

// Retrieves current vector size
size_t vector_size(const Vector *vector);

// Changes the vector size (may increase or decrease)
// Should be O(1) on average
void vector_resize(Vector *vector, size_t size);

#endif
