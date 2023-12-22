
#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>  
#include <utility>  

struct Vector;
Vector *vector_create(size_t initial_capacity = 10);
void vector_delete(Vector *vector);
std::pair<int, int> vector_get(const Vector *vector, size_t index); 
void vector_set(Vector *vector, size_t index, std::pair<int, int> value);
size_t vector_size(const Vector *vector);
void vector_resize(Vector *vector, size_t new_size);

#endif 