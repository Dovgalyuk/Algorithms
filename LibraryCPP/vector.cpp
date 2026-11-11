#include "vector.h"

struct Vector
{
    size_t size;
    size_t capacity;
    Data* data;

    Vector(): size(0), capacity(0), data(nullptr) {}

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
    if (!vector || index >= vector->size) return -1;
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (!vector) return;

    if (index >= vector->size) vector_resize(vector, index + 1);
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector ? vector->size : 0;
}

void vector_resize(Vector *vector, size_t size)
{
    if (!vector) return;
    if (size > vector->capacity) {
        size_t new_capacity = vector->capacity == 0 ? 2 : vector->capacity * 2;

        while (new_capacity < size) new_capacity = new_capacity * 2;

        Data* new_data = new Data[new_capacity]{};

        for (size_t i = 0; i < vector->size; i++) {
            new_data[i] = vector->data[i];
        }

        delete[] vector->data;
        vector->capacity = new_capacity;
        vector->data = new_data;
    }
    for (size_t i = vector->size; i < size; i++) {
        vector->data[i] = Data{};
    }
    vector->size = size;
}
