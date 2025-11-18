#include "vector.h"

Vector *vector_create()
{
    Vector* vec = new Vector;
    vec->data = nullptr;
    vec->size = 0;
    vec->capacity = 0;
    return vec;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        return (Data)0;
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        vector_resize(vector, index + 1);
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_capacity = (vector->capacity == 0) ? 1 : vector->capacity * 2;
        while (new_capacity < size) {
            new_capacity *= 2;
        }
        Data* new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    vector->size = size;
}
