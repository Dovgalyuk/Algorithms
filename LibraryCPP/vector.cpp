#include "vector.h"
#include <stdexcept>

struct Vector
{
    Data *data;
    size_t size;
    size_t capacity;
};

Vector *vector_create()
{
    return new Vector{nullptr, 0, 0};
}

void vector_delete(Vector *vector)
{
    if (vector == nullptr)
        return;

    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (vector == nullptr || index >= vector->size)
        throw std::out_of_range("Invalid vector index");

    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector == nullptr || index >= vector->size)
        throw std::out_of_range("Invalid vector index");

    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector == nullptr ? 0 : vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector == nullptr)
        throw std::invalid_argument("Null vector");

    if (size > vector->capacity)
    {
        size_t new_capacity = vector->capacity == 0 ? 1 : vector->capacity;

        while (new_capacity < size)
        {
            if (new_capacity > static_cast<size_t>(-1) / 2)
            {
                new_capacity = size;
                break;
            }

            new_capacity *= 2;
        }

        Data *new_data = new Data[new_capacity]{};

        for (size_t i = 0; i < vector->size; ++i)
            new_data[i] = vector->data[i];

        delete[] vector->data;

        vector->data = new_data;
        vector->capacity = new_capacity;
    }
    else if (size > vector->size)
    {
        for (size_t i = vector->size; i < size; ++i)
            vector->data[i] = 0;
    }

    vector->size = size;
}
