#ifndef VECTOR_H
#define VECTOR_H

// Vector (dynamic array)
// Stores integer values inside
typedef int Data;

struct Vector;

// Creates vector
Vector *vector_create();

// Deletes vector structure and internal data
void vector_delete(Vector *vector);

// Retrieves vector element with the specified index
Data vector_get(Vector *vector, size_t index);

// Sets vector element with the specified index
void vector_set(Vector *vector, size_t index, Data value);

// Retrieves current vector size
size_t vector_size(Vector *vector);

// Changes the vector size (may increase or decrease)
// Should be O(1) on average
void vector_resize(Vector *vector, size_t size);

#endif
