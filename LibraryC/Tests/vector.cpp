#include <iostream>
#include <stdio.h>
#include "vector.h"

void myfree(void *p)
{
    delete (int*)p;
}

int vector_get_int(Vector *v, size_t i) {
    if (v == nullptr) {
        std::cerr << "Ошибка: вектор пуст!\n";
        return -1;
    }


    if (i >= vector_size(v)) {
        std::cerr << "Ошибка: индекс " << i << " вне границ вектора.\n";
        return -1;
    }
       
    Data data = vector_get(v, i);
    if (data == nullptr) {
        std::cerr << "Ошибка: данные по индексу " << i << " являются NULL!\n";
        return -1;
    }

    return *(int *)data; // Убедитесь, что это безопасно
}

int main() {
    Vector *vector = vector_create(2, myfree);
    if (!vector) {
        std::cerr << "Ошибка: не удалось создать вектор.\n";
        return 1;
    }

    vector_resize(vector, 5);
    if (vector_size(vector) != 5)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        vector_set(vector, i, new int(i));

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

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i) {
        if (vector_get_int(vector, i) != int(-1))
            std::cout << vector_get_int(vector, i) << " ";
        else
            break;
    }
    std::cout << "\n";

    vector_resize(vector, 3);
    std::cout << "Vector3: ";
    if (vector_size(vector) != 3)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }
    std::cout << "Vector3: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    {
        if (vector_get_int(vector, i) != (int)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        std::cout << vector_get_int(vector, i) << " ";
    std::cout << "\n";

    // Performance test
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        vector_resize(vector, i);
        vector_set(vector, i - 1, new int(i));
    }

    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i)
        sum += vector_get_int(vector, i);

    std::cout << sum << "\n";

    vector_delete(vector);
    return 0;
}
