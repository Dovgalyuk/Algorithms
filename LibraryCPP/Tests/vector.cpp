#include <cstddef>
#include <iostream>
#include "vector.h"

static bool check_size(const Vector *vector, std::size_t expected)
{
    if (vector_size(vector) != expected)
    {
        std::cerr << "Expected vector size: " << expected << "\n";
        return false;
    }

    return true;
}

static bool check_value(const Vector *vector, std::size_t index, Data expected)
{
    if (vector_get(vector, index) != expected)
    {
        std::cerr << "Expected " << expected << " at vector index " << index << "\n";
        return false;
    }

    return true;
}

static bool test_vector(Vector *vector)
{
    if (!check_size(vector, 0))
        return false;

    vector_resize(vector, 5);
    if (!check_size(vector, 5))
        return false;

    for (std::size_t index = 0; index < 5; ++index)
    {
        if (!check_value(vector, index, 0))
            return false;
        vector_set(vector, index, static_cast<Data>(index) + 1);
    }

    vector_resize(vector, 257);
    if (!check_size(vector, 257))
        return false;

    for (std::size_t index = 0; index < 5; ++index)
    {
        if (!check_value(vector, index, static_cast<Data>(index) + 1))
            return false;
    }
    for (std::size_t index = 5; index < 257; ++index)
    {
        if (!check_value(vector, index, 0))
            return false;
    }

    vector_resize(vector, 3);
    if (!check_size(vector, 3))
        return false;

    vector_resize(vector, 6);
    if (!check_size(vector, 6))
        return false;

    for (std::size_t index = 0; index < 3; ++index)
    {
        if (!check_value(vector, index, static_cast<Data>(index) + 1))
            return false;
    }
    for (std::size_t index = 3; index < 6; ++index)
    {
        if (!check_value(vector, index, 0))
            return false;
    }

    vector_resize(vector, 0);
    if (!check_size(vector, 0))
        return false;

    vector_resize(vector, 1);
    if (!check_size(vector, 1) || !check_value(vector, 0, 0))
        return false;

    const std::size_t element_count = 10000000;
    for (std::size_t index = 0; index < element_count; ++index)
    {
        vector_resize(vector, index + 1);
        vector_set(vector, index, static_cast<Data>(index) + 1);
    }

    if (!check_size(vector, element_count))
        return false;

    for (std::size_t index = 0; index < element_count; ++index)
    {
        if (!check_value(vector, index, static_cast<Data>(index) + 1))
            return false;
    }

    return true;
}

int main()
{
    Vector *vector = vector_create();
    bool passed = test_vector(vector);
    vector_delete(vector);
    return passed ? 0 : 1;
}
