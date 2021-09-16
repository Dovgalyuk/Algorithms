#include "vector.h"

struct Vector
{
    size_t length;
    size_t capacity;
    const int capacity_multiply = 2;
    Data* data;

    Vector(): length(0), capacity(0), data(nullptr) {}

    void data_copy(Data* new_data, size_t size, size_t offset_old_data = 0, size_t offset_new_data = 0) const {
        for (int i = 0; i < size; ++i) {
            new_data[offset_new_data + i] = data[offset_old_data + i];
        }
    }
};

void vector_reserve(Vector *vector, size_t size) {
    if (vector->capacity >= size)
        return;
    if (vector->capacity == 0)
        vector->capacity = 1;
    while (vector->capacity < size)
        vector->capacity *= vector->capacity_multiply;

    Data* new_data = new Data[vector->capacity];
    vector->data_copy(new_data, vector->length);
    delete[] vector->data;
    vector->data = new_data;
}

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete[] vector->data;
    delete vector;
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
    return vector->length;
}

void vector_resize(Vector *vector, size_t size)
{
    vector_reserve(vector, size);
    vector->length = size;
}
