#include <iostream>
#include "vector.h"

int main()
{
    Vector *vector = vector_create();

    vector_resize(vector, 5);
    if (vector_capacity(vector) != 5)
        std::cout << "Invalid resize\n";

    for (size_t i = 0 ; i < vector_capacity(vector) ; ++i)
        vector_set(vector, i, i);

    for (size_t i = 0 ; i < vector_capacity(vector) ; ++i)
        if (vector_get(vector, i) != i)
            std::cout << "Invalid vector element " << i << "\n";

    vector_resize(vector, 10);
    if (vector_capacity(vector) != 10)
        std::cout << "Invalid resize\n";

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_capacity(vector) ; ++i)
        std::cout << vector_get(vector, i) << " ";
    std::cout << "\n";

    vector_resize(vector, 3);
    if (vector_size(vector) != 3)
        std::cout << "Invalid resize\n";

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        if (vector_get(vector, i) != i)
            std::cout << "Invalid vector element " << i << "\n";

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        std::cout << vector_get(vector, i) << " ";
    std::cout << "\n";

    // Performance test
    for (int i = 0 ; i < 10000000 ; ++i)
        vector_resize(vector, i);

    vector_delete(vector);
}
