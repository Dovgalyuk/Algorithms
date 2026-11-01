#include <limits>
#include <memory>
#include <stdexcept>
#include "vector.h"

struct Vector
{
    Data *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
};

Vector *vector_create()
{
    return new Vector;
}

void vector_delete(Vector *vector)
{
    if (!vector)
        return;
    delete[] vector->data;
    delete vector;
}

Data vector_get(const Vector *vector, size_t index)
{
    if (index >= vector->size)
        throw std::out_of_range("Vector index out of range");
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (index >= vector->size)
        throw std::out_of_range("Vector index out of range");
    vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    const size_t max_size = std::numeric_limits<size_t>::max() / sizeof(Data);
    if (size > max_size)
        throw std::length_error("Vector is too large");
    if (size > vector->capacity)
    {
        size_t capacity = vector->capacity ? vector->capacity : 1;
        while (capacity < size)
        {
            if (capacity > max_size / 2)
            {
                capacity = max_size;
                break;
            }
            capacity *= 2;
        }
        std::unique_ptr<Data[]> data(new Data[capacity]);
        for (size_t i = 0; i < vector->size; ++i)
            data[i] = vector->data[i];
        delete[] vector->data;
        vector->data = data.release();
        vector->capacity = capacity;
    }
    // Shrinking keeps capacity; new elements are always initialized to zero.
    for (size_t i = vector->size; i < size; ++i)
        vector->data[i] = 0;
    vector->size = size;
}
