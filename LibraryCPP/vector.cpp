#include "vector.h"

struct Vector
{
    size_t size = 0;
    size_t capacity = 0;
    Data *vector = nullptr;

    Vector() = default;

    ~Vector() {
        delete[] vector;
    }
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    // TODO: free vector internals
    delete vector; 
}

Data vector_get(const Vector *vector, size_t index)
{
    if (!vector || index >= vector->size) {
        return Data();
    }

    return vector->vector[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (!vector) return;

    if (index >= vector->size) {
        vector_resize(vector, index + 1);
    }

    vector->vector[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (!vector) {
        return;
    }

    if (size > vector->capacity) {
        size_t new_capacity = size * 2;
        Data *new_data = new Data[new_capacity]{};

        if (vector->vector) {
            for (size_t i = 0; i < vector->size; i++) {
                new_data[i] = vector->vector[i];
            }
            delete[] vector->vector;
        }
        vector->vector = new_data;
        vector->capacity = new_capacity;
    }

    vector->size = size;
}
