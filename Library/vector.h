#include <iostream>
#ifndef VECTOR_H
#define VECTOR_H

// Vector (dynamic array) of integers

struct Vector;

// Creates vector
Vector *vector_create();

// Deletes vector structure and internal data
void vector_delete(Vector *vector);

// Retrieves vector element with the specified index
int vector_get(Vector *vector, size_t index);

// Sets vector element with the specified index
void vector_set(Vector *vector, size_t index, int value);

// Retrieves current vector size
size_t vector_size(Vector *vector);

// Changes the vector size (may increase or decrease)
void vector_resize(Vector *vector, size_t size);

#endif
