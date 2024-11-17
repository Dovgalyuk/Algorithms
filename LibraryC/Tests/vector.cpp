#include <iostream> 
#include <stdio.h> 
#include "vector.h" 

void myfree(void *p)
{
    delete (int*)p;
}

int vector_get_int(Vector *v, size_t i)
{
    return *(int*)vector_get(v, i);
}

int main()
{
    Vector *vector = vector_create(1, myfree);
    if (!vector) { // Проверяем, была ли успешна работа функции создания вектора
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
    //     int value = vector_get_int(vector, i);
    //     if (vector_get_int(vector, i) == -1) { // Если возникла ошибка, прерываем цикл
    //         break; 
    //     }
    //     std::cout << value << " "; // Выводим значение
    //     //std::cout << "Done!\n "; // Выводим значение
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
    //     if (vector_get_int(vector, i) == -1) { // Если возникла ошибка, прерываем цикл
    //         break; 
    //     }
    //     std::cout << vector_get_int(vector, i) << " "; // Выводим значение
    // }
    // std::cout << "\n";

    // // Performance test
    // for (int i = 1 ; i <= 10000000; ++i)
    // {
    //     vector_resize(vector, i);
    //     vector_set(vector, i - 1, new int(i));
    // }

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
