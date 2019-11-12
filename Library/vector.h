#ifndef VECTOR_H
#define VECTOR_H


typedef int Data;

struct Vector;

Vector *vector_create();

void vector_delete(Vector *vector);

Data vector_get(const Vector *vector, size_t index);

void vector_set(Vector *vector, size_t index, Data value);

size_t vector_size(const Vector *vector);

void vector_resize(Vector *vector, size_t size);

#endif
