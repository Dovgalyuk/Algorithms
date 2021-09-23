#include <iostream>
#include <random>
#include <ctime>
#include "array.cpp"

using std::cout;
using std::cin;

void random_number_generation(Array *array) {
    std::mt19937 mersenne(time(0)); // создание генератора случайных чисел и инициализация его значением time(0)
    std::uniform_int_distribution<int> dist(0, 70); // создание распределения dist, инициализация его начальным значениями

    for (int index = 0; index < array_size(array); index++) {
        array_set(array, index, dist(mersenne)); // заполнение массива случайными числами из данного распределения, созданная с помощью mersenne
    }
}

void print(Array *array) {
    for (int index = 0; index < array_size(array); index++) {
        cout << array_get(array, index) << " ";
    }

    cout << "\n";
}

void condition_a(Array *array) {
    // верно ли, что сумма элементов, которые больше 20, превышает 100
    int sum_1 = 0;

    for (int index = 0; index < array_size(array); index++) {
        if (array_get(array, index) > 20) {
            sum_1 += array_get(array, index);
        }
        else {
            continue; // Можно и без этого???
        }
    }

    cout << sum_1 << std::endl; // Сумма для условия A

    if (sum_1 > 100) {
        cout << "The sum of the elements that are greater than 20 exceeds 100 - TRUE\n";
    }
    else {
        cout << "The sum of the elements that are greater than 20 exceeds 100 - FALSE\n";
    }
}

void condition_b(Array *array) {
    // верно ли, что сумма элементов, которые меньше 50, есть четное число
    int sum_2 = 0;

    for (int index = 0; index < array_size(array); index++) {
        if (array_get(array, index) < 50) {
            sum_2 += array_get(array, index);
        }
        else {
            continue;
        }
    }

    cout << sum_2 << std::endl; // Сумма для условия B
    
    if (sum_2 % 2 == 0) {
        cout << "The sum of elements that are less than 50 is an even number - TRUE\n";
    }
    else {
        cout << "The sum of elements that are less than 50 is an even number - FALSE\n";
    }
}

int main() {

    // Создание массива Array и заполнение
    int size_array;
    cout << "Enter the array size: ";
    cin >> size_array;

    Array* array = array_create(size_array);
    random_number_generation(array);

    // Ввывод Array
    print(array);

    // Условие A
    condition_a(array);

    // Условие B
    condition_b(array);

    array_delete(array);
    
    return 0;
}