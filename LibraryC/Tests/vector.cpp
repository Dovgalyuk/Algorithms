#include <iostream>
#include <stdio.h>
#include "vector.h" // Предполагается, что ваш интерфейс Vector доступен

void myfree(void *p) {
    delete (int*)p; // Освобождаем память, выделенную под int
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

    return *(int*)data; // Предполагаем, что это безопасно
}

int main() {
    const size_t initialVectorSize = 10000000; // Оптимальное начальное значение
    Vector *vector = vector_create(initialVectorSize, myfree); // Создаем вектор с заданным размером

    if (!vector) {
        std::cerr << "Ошибка: не удалось создать вектор.\n";
        return 1;
    }

    // Заполняем вектор значениями
    for (size_t i = 0; i < initialVectorSize; ++i) {
        vector_set(vector, i, new int(i)); // Устанавливаем значение по индексу
    }

    // Вывод значений
    std::cout << "Vector: ";
    for (size_t i = 0; i < initialVectorSize; ++i) {
        int value = vector_get_int(vector, i);
        if (value == -1) {
            break; // Завершаем цикл, если произошла ошибка
        }
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Подсчет суммы
    long long sum = 0;
    for (size_t i = 0; i < initialVectorSize; ++i) {
        sum += vector_get_int(vector, i);
    }

    std::cout << "Sum: " << sum << "\n";

    // Освобождение ресурсов
    vector_delete(vector); // Предполагаем, что vector_delete корректно освобождает память
    return 0;
}