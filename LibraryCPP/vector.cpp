#include "vector.h"

struct Vector
{
    size_t length;
    size_t capacity;
    const int capacity_multiply = 2;
    Data* data;

    Vector(): length(0), capacity(0), data(nullptr) {}
};

void vector_data_copy(Vector* vector, Data* new_data, size_t size, size_t offset_old_data, size_t offset_new_data) {
    for (int i = 0; i < size; ++i) {
        new_data[offset_new_data + i] = vector->data[offset_old_data + i];
    }
}

void vector_set_data(Vector* vector, Data* new_data, size_t size) {
    delete[] vector->data;
    vector->data = new_data;
    vector->length = size;
}

void vector_expand_data(Vector* vector, size_t size) {
    if (vector->capacity >= size)
        return;
    if (vector->capacity == 0)
        vector->capacity = 1;
    while (vector->capacity < size)
        vector->capacity *= vector->capacity_multiply;
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
    if (vector->capacity < size) {
        vector_expand_data(vector, size);
        Data* new_data = new Data[vector->capacity];
        vector_data_copy(vector, new_data, vector_size(vector));
        vector_set_data(vector, new_data, size);
    } else {
        vector->length = size;
    }
}
