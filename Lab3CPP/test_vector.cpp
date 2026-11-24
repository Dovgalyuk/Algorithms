#include <iostream>
#include <stdexcept>
#include "vector.h"

int main()
{
    Vector* v = vector_create();

    if (vector_size(v) != 0)
        return 1;

    vector_resize(v, 5);

    if (vector_size(v) != 5)
        return 1;

    for (size_t i = 0; i < 5; ++i)
        vector_set(v, i, static_cast<int>(i + 1));

    for (size_t i = 0; i < 5; ++i)
    {
        if (vector_get(v, i) != static_cast<int>(i + 1))
            return 1;
    }

    vector_resize(v, 100);

    if (vector_size(v) != 100)
        return 1;

    for (size_t i = 0; i < 5; ++i)
    {
        if (vector_get(v, i) != static_cast<int>(i + 1))
            return 1;
    }

    for (size_t i = 5; i < 100; ++i)
    {
        if (vector_get(v, i) != 0)
            return 1;
    }

    vector_resize(v, 3);

    if (vector_size(v) != 3)
        return 1;

    for (size_t i = 0; i < 3; ++i)
    {
        if (vector_get(v, i) != static_cast<int>(i + 1))
            return 1;
    }

    bool exceptionCaught = false;

    try
    {
        vector_get(v, 10);
    }
    catch (const std::out_of_range&)
    {
        exceptionCaught = true;
    }

    if (!exceptionCaught)
        return 1;

    vector_delete(v);

    std::cout << "Vector tests passed\n";
    return 0;
}
