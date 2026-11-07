#include <iostream>
#include "vector.h"

int main()
{
    Vector* vector = vector_create();

    vector_resize(vector, 3);
    vector_set(vector, 0, 10);
    vector_set(vector, 1, 20);
    vector_set(vector, 2, 30);

    vector_resize(vector, 10);

    if (vector_size(vector) != 10 ||
        vector_get(vector, 0) != 10 ||
        vector_get(vector, 1) != 20 ||
        vector_get(vector, 2) != 30)
    {
        std::cout << "Vector resize error\n";
        vector_delete(vector);
        return 1;
    }

    for (int i = 0; i < 1000; ++i)
    {
        vector_resize(vector, i + 1);
        vector_set(vector, i, i);
    }

    for (int i = 0; i < 1000; ++i)
    {
        if (vector_get(vector, i) != i)
        {
            std::cout << "Vector element error\n";
            vector_delete(vector);
            return 1;
        }
    }

    vector_resize(vector, 5);
    if (vector_size(vector) != 5 || vector_get(vector, 4) != 4)
    {
        std::cout << "Vector shrink error\n";
        vector_delete(vector);
        return 1;
    }

    vector_delete(vector);
    std::cout << "Vector tests passed\n";
    return 0;
}
