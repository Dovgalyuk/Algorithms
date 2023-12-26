#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Vector (dynamic array)
// Stores pointer to custom user data
typedef void* Data;
// Custom function to free user pointers on delete
typedef void (FFree)(void*);

typedef struct Vector Vector;

#ifdef __cplusplus
extern "C" {
#endif

// Creates vector
Vector *vector_create(FFree f);

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

#ifdef __cplusplus
}
#endif

#endif
