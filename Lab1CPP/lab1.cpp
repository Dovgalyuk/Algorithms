#include <iostream>
#include <random>
#include <limits> // Для получения минимального значения int
#include <unordered_map> // Для подсчета частоты элементов массива
#include "../LibraryCPP/array.h" // Подключаем заголовочный файл с определением структуры Array и функций для работы с массиво

using namespace std;

// Функция для заполнения массива случайными числами в заданном диапазоне
void fillRandom(Array* arr, int minVal, int maxVal) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    for (size_t i = 0; i < array_size(arr); ++i) {
        array_set(arr, i, distrib(gen));
    }
}
// Функция для нахождения максимального элемента среди элементов с четными индексами
// Принимает указатель на массив (Array* arr), минимальное значение (int minVal) и максимальное значение (int maxVal)
Data findMaxEvenIndex(const Array* arr) {
    size_t size = array_size(arr);

    std::cerr << "findMaxEvenIndex: size = " << size << std::endl; // Добавлено

    if (size == 0) {
        std::cerr << "findMaxEvenIndex: Array is empty, returning min!!!!!" << std::endl;
        return numeric_limits<Data>::min();
    }

    //if (!size % 2 > 0)size -= 1;

    // Инициализируем максимальное значение минимальным возможным значением типа Data
    Data maxVal = numeric_limits<Data>::min();

    // Проходим по элементам массива с четными индексами
    for (size_t i = 0; i < size; i += 2) {
        Data val = array_get(arr, i);
        if (val > maxVal) {
            maxVal = val;
        }
    }

    return maxVal;
}
// Функция для определения наиболее часто встречающегося числа в массиве
// Принимает указатель на массив (const Array* arr)
Data findMostFrequent(const Array* arr) {
    size_t size = array_size(arr);

    // Создаем unordered_map для подсчета частоты каждого элемента
    // Ключ - элемент массива (Data), значение - количество вхождений этого элемента
    unordered_map<Data, int> counts;

    // Проходим по всем элементам массива
    for (size_t i = 0; i < size; ++i) {
        counts[array_get(arr, i)]++;
    }

    // Инициализируем наиболее часто встречающийся элемент первым элементом массива
    Data mostFrequent = array_get(arr, 0);

    // Инициализируем максимальное количество вхождений нулем
    int maxCount = 0;

    // Проходим по всем парам (элемент, количество вхождений) в unordered_map
    for (const auto& pair : counts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequent = pair.first;
        }
    }

    return mostFrequent;
}

int main() {

    // 1. Поиск максимального элемента среди элементов с четными индексами

    size_t size1;
    //cout << "Введите размер первого массива: ";
    cin >> size1;

    Array* arr1 = array_create(size1);

    fillRandom(arr1, 1, 100); // Заполняем случайными числами от 1 до 100

    /*cout << "Массив 1: ";
    for (size_t i = 0; i < array_size(arr1); ++i) {
        cout << array_get(arr1, i) << " ";
    }
    cout << endl;*/

    Data maxEven = findMaxEvenIndex(arr1);
    //cout << "Максимальный элемент с четным индексом: " << maxEven << endl;
    cout << maxEven << endl;

    // Освобождаем память
    array_delete(arr1);


    // 2. Определение наиболее часто встречающегося числа


    size_t size2;
    //cout << "Введите размер второго массива: ";
    cin >> size2;

    Array* arr2 = array_create(size2);

    fillRandom(arr2, 1, 10); // Заполняем случайными числами от 1 до 10

    ///*cout << "Массив 2: ";
    //for (size_t i = 0; i < array_size(arr2); ++i) {
    //    cout << array_get(arr2, i) << " ";
    //}
    //cout << endl;*/

    Data mostFrequent = findMostFrequent(arr2);
    //cout << "Наиболее часто встречающееся значение: " << mostFrequent << endl;
    cout << mostFrequent << endl;

    // Освобождаем память
    array_delete(arr2);

    return 0;
}