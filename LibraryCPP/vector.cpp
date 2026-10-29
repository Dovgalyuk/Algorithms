#include "vector.h"
#include <algorithm>

struct Vector
{
    Data* data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    if (vector == nullptr) {
        return;
    }

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
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (size > vector->capacity) {
        size_t new_capacity = std::max(size, vector->capacity == 0? size_t{4} : vector->capacity * 2);

        Data* new_data = new Data[new_capacity];

        for (size_t i = 0; i < vector->size; ++i) {
            new_data[i] = vector->data[i];
        }

        delete[] vector->data;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    if (size > vector->size) {
        for (size_t i = vector->size; i < size; ++i) {
            vector->data[i] = Data{};
        }
    }

    vector->size = size;
}
