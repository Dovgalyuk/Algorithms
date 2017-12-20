#ifndef VECTOR_H
#define VECTOR_H

struct Vector;

Vector *vector_create();

void vector_delete(Vector *vector);

int vector_get(Vector *vector, size_t index);

void vector_set(Vector *vector, size_t index, int value);

size_t vector_size(Vector *vector);

void vector_resize(Vector *vector, size_t size);

#endif
