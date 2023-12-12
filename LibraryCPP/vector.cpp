#include "vector.h"

struct Vector
{
    size_t size;
    size_t capacity;
    Data* data;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = vector->capacity = 0;
    vector->data = nullptr;

    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return (index >= vector->capacity)? -1 : vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector->size == index)
        vector_resize(vector, (index + 1) );

    if (index < vector_size(vector)) {
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector->capacity >= size) {
        vector->size = size;
    }
    else {
        size_t capacity_scale_2x = size * 2;
        Data* temp = new Data[capacity_scale_2x];
        for (size_t i = 0; i < vector->size; i++) {
            temp[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->size = size;
        vector->capacity = capacity_scale_2x;
        vector->data = temp;
    }
}
