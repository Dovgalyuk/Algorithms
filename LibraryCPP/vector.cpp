#include "vector.h"
#include <stdexcept>

struct Vector
{
    Data* data;
    size_t size;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->data = nullptr;
    vector->size = 0;
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if(index >= vector->size) throw std::out_of_range("vector index out of range");
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if(index >= vector->size) throw std::out_of_range("vector index out of range");
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    Data* data = new Data[size];
    size_t count = vector->size < size ? vector->size : size;
    for(size_t i = 0; i < count; i++) data[i] = vector->data[i];
    delete[] vector->data;
    vector->data = data;
    vector->size = size;
}
