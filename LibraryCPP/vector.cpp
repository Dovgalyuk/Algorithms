#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t max_size;

    Vector() {
        size = 0;
        max_size = 1;
        data = new Data[max_size];
    }

    ~Vector() {
        delete[] data;
    }
};

Vector* vector_create()
{
    return new Vector;
}

void vector_delete(Vector* vector)
{
    delete vector;
}

Data vector_get(const Vector* vector, size_t index)
{
    if (index >= vector->size) {
        return (Data)0;
    }
    return vector->data[index];
}

void vector_set(Vector* vector, size_t index, Data value)
{
    if (index >= vector->size) {
        return;
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector* vector)
{
    return vector->size;
}

void vector_resize(Vector* vector, size_t size)
{
    if (size <= vector->max_size) {
        vector->size = size;
        return;
    }
    size_t _max_size = size * 2;
    Data* tmp = new Data[_max_size];
    for (size_t i = 0; i < vector->size; i++) {
        tmp[i] = vector->data[i];
    }
    delete[] vector->data;

    vector->data = tmp;
    vector->max_size = _max_size;
    vector->size = size;
}