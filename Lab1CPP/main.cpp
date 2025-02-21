#include "array.h"
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace std;

// Находит элементы больше среднего min и max, выводит их количество и индексы.
void task1(const Array* arr) {
    if (array_size(arr) == 0) return;

    int min = array_get(arr, 0);
    int max = array_get(arr, 0);

    for (size_t i = 1; i < array_size(arr); ++i) {
        int cur = array_get(arr, i);
        if (cur < min) min = cur;
        if (cur > max) max = cur;
    }

    double avg = (min + max) / 2.0;

    cout << "Количество элементов больших среднего арифметического: ";
    size_t count = 0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) > avg) {
            count++;
        }
    }
    cout << count << endl;

    cout << "Индексы: ";
    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) > avg) {
            cout << i << " ";
        }
    }
    cout << endl;
}
// Находит и выводит самый часто встречающийся элемент и количество его вхождений
void task2(const Array* arr) {
    if (array_size(arr) == 0) return;

    unordered_map<int, int> frequencyMap;

    for (size_t i = 0; i < array_size(arr); ++i) {
        frequencyMap[array_get(arr, i)]++;
    }

    int mostFrequent = array_get(arr, 0);
    int maxCount = 1;
    for (const auto& pair : frequencyMap) {
        if (pair.second > maxCount) {
            mostFrequent = pair.first;
            maxCount = pair.second;
        }
    }

    cout << "Самое частое число: " << mostFrequent << " встречается " << maxCount << " раз" << endl;
}
int main() {
    setlocale(LC_ALL, "Russian");
    size_t size;

    cout << "Введите размер массива: ";
    cin >> size;

    if (size <= 0) {
        throw std::invalid_argument("Размер массива не может быть равен нулю");
    }
    Array* arr = array_create(size);

    srand(static_cast<unsigned int>(time(0))); 
    for (size_t i = 0; i < size; ++i) {
        array_set(arr, i, rand() % 100);
    }

    cout << "Массив: ";
    for (size_t i = 0; i < size; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    task1(arr);
    task2(arr);

    array_delete(arr);

    return 0;
}