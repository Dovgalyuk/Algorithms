#ifndef VECTOR_H
#define VECTOR_H

// Vector (dynamic array)
// Stores integer values inside
typedef int Data;

typedef unsigned long long mysize_t;

struct Vector;

// Creates vector
Vector *vector_create();

// Deletes vector structure and internal data
void vector_delete(Vector *vector);

// Retrieves vector element with the specified index
Data vector_get(const Vector *vector, mysize_t index);

// Sets vector element with the specified index
void vector_set(Vector *vector, mysize_t index, Data value);

// Retrieves current vector size
mysize_t vector_size(const Vector *vector);

// Changes the vector size (may increase or decrease)
// Should be O(1) on average
void vector_resize(Vector *vector, mysize_t size);

#endif
