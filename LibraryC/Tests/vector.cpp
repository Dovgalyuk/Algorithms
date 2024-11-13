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

int main()
{
    Vector *vector = vector_create(10000000, myfree);
    if (!vector) { // Проверяем, была ли успешна работа функции создания вектора
        std::cerr << "Ошибка: не удалось создать вектор.\n"; 
        return 1;
    }

    // vector_resize(vector, 5);
    // if (vector_size(vector) != 5)
    // {
    //     std::cout << "Invalid resize\n";
    //     return 1;
    // }

    // for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    //     vector_set(vector, i, new int(i));

    // for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    // {
    //     if (vector_get_int(vector, i) != (int)i)
    //     {
    //         std::cout << "Invalid vector element " << i << "\n";
    //         return 1;
    //     }
    // }

    // vector_resize(vector, 10);
    // if (vector_size(vector) != 10)
    // {
    //     std::cout << "Invalid resize\n";
    //     return 1;
    // }

    // // Выводим значения из вектора на экран
    // std::cout << "Vector: ";
    // for (size_t i = 0; i < vector_size(vector); ++i) {
    //     int value = vector_get_int(vector, i); // Получаем значение из вектора
    //     if (value == -1) { // Если возникла ошибка, прерываем цикл
    //         break; 
    //     }
    //     std::cout << value << " "; // Выводим значение
    // }
    // std::cout << "\n";

    // vector_resize(vector, 3);
    // if (vector_size(vector) != 3)
    // {
    //     std::cout << "Invalid resize\n";
    //     return 1;
    // }

    // for (size_t i = 0 ; i < vector_size(vector) ; ++i)
    // {
    //     if (vector_get_int(vector, i) != (int)i)
    //     {
    //         std::cout << "Invalid vector element " << i << "\n";
    //         return 1;
    //     }
    // }

    // // Выводим значения из вектора на экран
    // std::cout << "Vector: ";
    // for (size_t i = 0; i < vector_size(vector); ++i) {
    //     int value = vector_get_int(vector, i); // Получаем значение из вектора
    //     if (value == -1) { // Если возникла ошибка, прерываем цикл
    //         break; 
    //     }
    //     std::cout << value << " "; // Выводим значение
    // }
    // std::cout << "\n";

    // Performance test
    for (int i = 1 ; i <= 250000; ++i)
    {
        vector_resize(vector, i);
        //vector_set(vector, i - 1, new int(i));
    }

    // long long sum = 0;
    // for (int i = 0 ; i < 10000000 ; ++i)
    //     sum += vector_get_int(vector, i);

    // std::cout << sum << "\n";

    vector_delete(vector);
    return 0;
}

// int main() {
//     Vector *vector = vector_create(1, myfree); // Создаем вектор с начальным размером и функцией освобождения

//     if (!vector) { // Проверяем, была ли успешна работа функции создания вектора
//         std::cerr << "Ошибка: не удалось создать вектор.\n"; 
//         return 1;
//     }

//     vector_resize(vector, 10);
//     if (vector_size(vector) != 10)
//     {
//         std::cout << "Invalid resize\n";
//         return 1;
//     }

//     // Заполняем вектор значениями от 0 до initialVectorSize-1
//     for (size_t i = 0; i < vector_size(vector); ++i) {
//         vector_set(vector, i, new int(i)); // Создаем новый int и сохраняем его в вектор
//     }

//     // Выводим значения из вектора на экран
//     std::cout << "Vector: ";
//     for (size_t i = 0; i < vector_size(vector); ++i) {
//         int value = vector_get_int(vector, i); // Получаем значение из вектора
//         if (value == -1) { // Если возникла ошибка, прерываем цикл
//             break; 
//         }
//         std::cout << value << " "; // Выводим значение
//     }
//     std::cout << "\n";

//     vector_resize(vector, 15);
//     if (vector_size(vector) != 15)
//     {
//         std::cout << "Invalid resize\n";
//         return 1;
//     }

//     std::cout << "Vector: ";
//     for (size_t i = 0; i < vector_size(vector); ++i) {
//         int value = vector_get_int(vector, i); // Получаем значение из вектора
//         if (value == -1) { // Если возникла ошибка, прерываем цикл
//             break; 
//         }
//         std::cout << value << " "; // Выводим значение
//     }
//     std::cout << "\n";

//     // Считаем сумму значений вектора
//     long long sum = 0;
//     for (size_t i = 0; i < initialVectorSize; ++i) {
//         sum += vector_get_int(vector, i); // Получаем значения и добавляем их к сумме
//     }
//     std::cout << "Sum: " << sum << "\n"; // Выводим сумму значений
    
//     vector_delete(vector); // Освобождаем память, занятую вектором
//     return 0; // Завершаем программу с кодом 0
// }
