#include <iostream>
#include "vector.h"

void myfree(void *p)
{
    delete (int*)p;
}

int vector_get_int(Vector *v, size_t i)
{
    // Проверка на выход за пределы вектора
    if (i >= vector_size(v)) {
        std::cout << "Index out of bounds: " << i << "\n";
        return -1; 
    }
    return *(int*)vector_get(v, i); // Возвращает значение элемента
}

int main()
{
    Vector *vector = vector_create(myfree);

    vector_resize(vector, 5);

    if (vector_size(vector) != 5)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector_size(vector) ; ++i) {
        vector_set(vector, i, new int(i));
    }

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    {
        if (vector_get_int(vector, i) != (int)i)
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

    std::cout << "Vector: " << std::endl;
    for (size_t i = 0; i < vector_size(vector); ++i) {
        if (vector_get(vector, i) == NULL) {
            break; 
        } else {
            std::cout << vector_get_int(vector, i) << " "; 
        }
    }
    std::cout << "\n";

    vector_resize(vector, 3);
    if (vector_size(vector) != 3)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }
    
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    {
        if (vector_get_int(vector, i) != (int)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    std::cout << "Vector: " << std::endl;
    for (size_t i = 0; i < vector_size(vector); ++i) {
        if (vector_get(vector, i) == NULL) {
            break; 
        } else {
            std::cout << vector_get_int(vector, i) << " "; 
        }
    }
    std::cout << "\n";

    std::cout << "Test starts" << std::endl;
    // Performance test
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        std::cout << "Current size: " << vector_size(vector) << ", Capacity: " << vector_capacity(vector) << ", i: " << i << "\n";
        vector_resize(vector, i);
        vector_set(vector, i - 1, new int(i));
        std::cout << "index = "<< i-1 <<", element = " << vector_get_int(vector, i) << std::endl;
    }
    
    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i) {
        sum += vector_get_int(vector, i);
    }
    std::cout << sum << "\n";

    vector_delete(vector);
}