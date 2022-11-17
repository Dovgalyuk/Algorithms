#include "vector.h"

struct Vector
{
    size_t size;
    size_t res_size;
    Data* data;
};

Vector *vector_create()
{
    Vector* vector = new Vector;
    vector->size = vector->res_size = 0;
    vector->data = new Data[vector->res_size];
    return vector;
}

void vector_delete(Vector *vector)
{
    delete[] vector->data;
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index < vector->size) {
        vector->data[index] = value;
    }
    else {
        vector_resize(vector, index + 1);
        vector->data[index] = value;
    }
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->res_size) {
        vector->size = size;
    }
    else {
        size_t new_size = size * 2;
        Data* new_data = new Data[new_size];
        for (size_t i = 0; i < vector->size; i++) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;

        vector->data = new_data;
        vector->size = size;
        vector->res_size = new_size;
    }
}
