#include <iostream>
#include "vector.h"

int main()
{
    Vector *vector = vector_create();

    vector_resize(vector, 5);
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        vector_set(vector, i, i);

    vector_resize(vector, 10);
    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        std::cout << vector_get(vector, i) << " ";
    std::cout << "\n";

    vector_resize(vector, 3);
    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        std::cout << vector_get(vector, i) << " ";
    std::cout << "\n";

    vector_delete(vector);
}
