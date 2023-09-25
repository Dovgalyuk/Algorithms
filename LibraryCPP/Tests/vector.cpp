#include <iostream>
#include "vector.h"

int main()
{
    Vector *vector = vector_create();

    vector_resize(vector, 5);
    if (vector_size(vector) != 5)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        vector_set(vector, i, i);

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    {
        if (vector_get(vector, i) != (int)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    vector_resize(vector, 10);
    if (vector_size(vector) != 10)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        std::cout << vector_get(vector, i) << " ";
    std::cout << "\n";

    vector_resize(vector, 3);
    if (vector_size(vector) != 3)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    {
        if (vector_get(vector, i) != (int)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        std::cout << vector_get(vector, i) << " ";
    std::cout << "\n";

    // Performance test
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        vector_resize(vector, i);
        vector_set(vector, i - 1, i);
    }

    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i)
        sum += vector_get(vector, i);

    std::cout << sum << "\n";

    vector_delete(vector);
}
