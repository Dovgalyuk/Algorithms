#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t size_max;

    Vector() {
        size = 1;
        size_max = 2;
        data = new Data[size_max];
    }

    ~Vector() {
        delete[] data;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size) {
        return Data();
    }
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size) {
        return;
    }
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size <= vector->size_max) {
        vector->size = size;
        return;
    }
    size_t size_new_max = size * 2;
    Data* current = new Data[size_new_max];
    for (int i = 0; i < vector->size; i++) {
        current[i] = vector->data[i];
    }

    delete[] vector->data;
    vector->data = current;
    vector->size = size;
    vector->size_max = size_new_max;
}
