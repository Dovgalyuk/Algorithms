#include "vector.h"
#include <limits>

using namespace std;

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
        return 0;

    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, Data value)
{
    if (vector != nullptr && index < vector->size)
        vector->data[index] = value;
}

size_t vector_size(const Vector *vector)
{
    return vector == nullptr ? 0 : vector->size;
}

void vector_resize(Vector *vector, size_t size)
{
    if (vector == nullptr)
        return;

    if (size > vector->capacity)
    {
        size_t capacity = vector->capacity == 0 ? 1 : vector->capacity;
        while (capacity < size)
        {
            if (capacity > numeric_limits<size_t>::max() / 2)
            {
                capacity = size;
                break;
            }
            capacity *= 2;
        }

        Data *data = new Data[capacity];
        for (size_t i = 0; i < vector->size; ++i)
            data[i] = vector->data[i];

        delete[] vector->data;
        vector->data = data;
        vector->capacity = capacity;
    }

    for (size_t i = vector->size; i < size; ++i)
        vector->data[i] = 0;

    vector->size = size;
}
