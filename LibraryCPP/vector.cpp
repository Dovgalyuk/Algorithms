#include "vector.h"

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    Vector* v = new Vector;
    v->data = nullptr;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void vector_delete(Vector *vector)
{
    if (!vector) return;
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size)
        throw std::out_of_range("vector_get: index out of range");
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size)
        throw std::out_of_range("vector_set: index out of range");
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_cap = vector->capacity ? vector->capacity : 1;
        while (new_cap < size) new_cap *= 2;

        Data* new_data = new Data[new_cap];
        for (size_t i = 0; i < vector->size; ++i)
            new_data[i] = vector->data[i];

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_cap;
    }

    for (size_t i = vector->size; i < size; ++i)
        vector->data[i] = Data();

    vector->size = size;
}
