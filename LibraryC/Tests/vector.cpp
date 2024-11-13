#include <iostream> 
#include <stdio.h> 
#include "vector.h" 

// Функция освобождения памяти, выделенной под данные в векторе
void myfree(void *p) {
    delete (int*)p; // Приводим указатель к типу int и освобождаем память
}

// Функция для получения значения типа int из вектора по индексу
int vector_get_int(Vector *v, size_t i) {
    if (v == nullptr) { // Проверяем, является ли вектор пустым
        std::cerr << "Ошибка: вектор пуст!\n"; 
        return -1; 
    }
    if (i >= vector_size(v)) { // Проверяем, находится ли индекс в границах вектора
        std::cerr << "Ошибка: индекс " << i << " вне границ вектора.\n"; 
        return -1; 
    }
    
    Data data = vector_get(v, i); // Получаем данные по индексу
    if (data == nullptr) { // Проверяем, не является ли полученное значение NULL
        std::cerr << "Ошибка: данные по индексу " << i << " являются NULL!\n"; 
        return -1; 
    }

    return *(int*)data; // Возвращаем значение по указателю, приводя его к типу int
}

int main() {
    const size_t initialVectorSize = 10000000; // Определяем начальный размер вектора
    Vector *vector = vector_create(initialVectorSize, myfree); // Создаем вектор с начальным размером и функцией освобождения

    if (!vector) { // Проверяем, была ли успешна работа функции создания вектора
        std::cerr << "Ошибка: не удалось создать вектор.\n"; 
        return 1;
    }

    // Заполняем вектор значениями от 0 до initialVectorSize-1
    for (size_t i = 0; i < initialVectorSize; ++i) {
        vector_set(vector, i, new int(i)); // Создаем новый int и сохраняем его в вектор
    }

    // Выводим значения из вектора на экран
    std::cout << "Vector: ";
    for (size_t i = 0; i < initialVectorSize; ++i) {
        int value = vector_get_int(vector, i); // Получаем значение из вектора
        if (value == -1) { // Если возникла ошибка, прерываем цикл
            break; 
        }
        std::cout << value << " "; // Выводим значение
    }
    std::cout << "\n";

    // Считаем сумму значений вектора
    long long sum = 0;
    for (size_t i = 0; i < initialVectorSize; ++i) {
        sum += vector_get_int(vector, i); // Получаем значения и добавляем их к сумме
    }

    std::cout << "Sum: " << sum << "\n"; // Выводим сумму значений

    vector_delete(vector); // Освобождаем память, занятую вектором
    return 0; // Завершаем программу с кодом 0
}
