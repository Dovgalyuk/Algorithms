#include "vector.h"

#include <cassert>
#include <limits>
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
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    assert(index < vector->size);
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    assert(index < vector->size);
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t new_size)
{
    if (new_size > vector->capacity)
    {
        const size_t max_size = std::numeric_limits<size_t>::max() / sizeof(Data);
        if (new_size > max_size)
            throw std::length_error("Vector слишком большой");

        // Удваиваем ёмкость, чтобы реже выделять память.
        size_t new_capacity = vector->capacity;
        if (new_capacity == 0)
            new_capacity = 1;

        while (new_capacity < new_size)
        {
            if (new_capacity > max_size / 2)
                new_capacity = max_size;
            else
                new_capacity *= 2;
        }

        Data *new_data = new Data[new_capacity];
        for (size_t i = 0; i < vector->size; ++i)
            new_data[i] = vector->data[i];

        delete[] vector->data;
        vector->data = new_data;
        vector->capacity = new_capacity;
    }

    // При уменьшении память сохраняется. Новые элементы заполняем нулями.
    for (size_t i = vector->size; i < new_size; ++i)
        vector->data[i] = 0;

    vector->size = new_size;
}
