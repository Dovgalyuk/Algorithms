#include <iostream>
#include <stdio.h>
#include "vector.h"

void myfree(void *p) {
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
    if (vector_size(vector) != 5) {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector_size(vector) ; ++i)
        vector_set(vector, i, new int(i));

    std::cout << "Vector: ";
    for (size_t i = 0; i < vector_size(vector); ++i) {
        int value = vector_get_int(vector, i);
        if (value == -1) { // Если возникла ошибка (например, NULL)
            break; // Завершить цикл, если элемент равен NULL
        }
        std::cout << value << " "; // Выводить значение, если нет ошибки
    }
    std::cout << "\n";

    // Производительный тест
    vector_resize(vector, 10000000); // Установите размер заранее
    for (int i = 0 ; i < 10000000 ; ++i)
    {
        vector_set(vector, i, new int(i));
    }

    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i)
        sum += vector_get_int(vector, i);

    std::cout << "Sum: " << sum << "\n";

    vector_delete(vector);
    return 0;
}