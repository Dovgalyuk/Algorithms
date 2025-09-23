#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include "array.h"

using namespace std;

// Функция для чтения из файла.

static Array* loadArray(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: файл не открыт!" << endl;
        return nullptr;
    }

    int n = 0;
    if (!(file >> n) || n <= 0) {
        cout << "Ошибка: размер <= 0!" << endl;
        return nullptr;
    }

    Array* arr = array_create(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) {
        int x = 0;
        file >> x;
        array_set(arr, static_cast<size_t>(i), x);
    }

    return arr;
}

// Задание 4.

static void task4(const string& filename) {
    Array* arr = loadArray(filename);
    if (!arr)
        return;

    long long sum = 0;
    const size_t n = array_size(arr);
    for (size_t i = 0; i < n; ++i)
        sum += array_get(arr, i);

    int count = 0;
    vector<size_t> indices;
    for (size_t i = 0; i < n; ++i) {
        if (array_get(arr, i) > sum) {
            ++count;
            indices.push_back(i);
        }
    }

    cout << "Task 4: Количество элементов > суммы (" << sum << "): " << count;
    if (count > 0) {
        cout << "\nНомера (от 0): ";
        for (size_t j = 0; j < indices.size(); ++j) {
            if (j)
                cout << ", ";

            cout << indices[j];
        }

        cout << endl;
    }
    else
        cout << ";";

    array_delete(arr);
}

// Задание 5.

static void task5(const string& filename) {
    Array* arr = loadArray(filename);
    if (!arr)
        return;

    const size_t n = array_size(arr);
    if (n < 5) {
        cout << "Task 5: Массив слишком маленький!" << endl;
        array_delete(arr);
        return;
    }
    
    int maxSum = INT_MIN;
    size_t start = 0;
    for (size_t i = 0; i + 5 <= n; ++i) {
        int s = 0;
        for (size_t k = 0; k < 5; ++k)
            s += array_get(arr, i + k);

        if (s > maxSum) {
            maxSum = s;
            start = i;
        }
    }

    cout << "Task 5: Максимальная сумма 5 соседних: " << maxSum << endl;
    cout << "Элементы: ";
    for (size_t k = 0; k < 5; ++k) {
        if (k)
            cout << ", ";

        cout << array_get(arr, start + k);
    }

    cout << endl;

    array_delete(arr);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Ошибка: укажите файл!" << endl;
        return 1;
    }

    string filename = argv[1];

    task4(filename);
    task5(filename);

    return 0;
}