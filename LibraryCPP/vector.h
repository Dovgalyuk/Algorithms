#ifndef VECTOR_H
#define VECTOR_H

typedef char Data;

struct Vector;

// Creates a new vector
Vector* vector_create();

// Deletes the vector and frees the memory
void vector_delete(Vector* vector);

// Gets the value at the specified index
Data vector_get(const Vector* vector, size_t index);

// Sets the value at the specified index
void vector_set(Vector* vector, size_t index, Data value);

// Gets the current size of the vector
size_t vector_size(const Vector* vector);

// Resizes the vector to the specified size
void vector_resize(Vector* vector, size_t size);

#endif