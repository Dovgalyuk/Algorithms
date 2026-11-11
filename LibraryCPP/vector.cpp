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
    v->size = 0;
    v->capacity = 10;
    v->data = new Data[v->capacity];
    return v;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    if (vector) {
        delete[] vector->data;
        delete vector;
    }
}

Data vector_get(const Vector *vector, size_t index)
{
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_cap = vector->capacity * 2;
        if (size > new_cap) new_cap = size;
        Data* new_data = new Data[new_cap];
        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_cap;
    }
    vector->size = size;
}
