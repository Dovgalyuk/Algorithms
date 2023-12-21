#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>  // for size_t

typedef char Data;  
struct Vector
{
    Data *data;      
    size_t capacity;  
    size_t size;      
};

Vector *vector_create(size_t initial_capacity = 10);
void vector_delete(Vector *vector);
Data vector_get(const Vector *vector, size_t index);
void vector_set(Vector *vector, size_t index, Data value);
size_t vector_size(const Vector *vector);
void vector_resize(Vector *vector, size_t new_size);

#endif