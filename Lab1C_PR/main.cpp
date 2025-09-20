/*#include <iostream>
#include <fstream> // Для файлов.
#include <vector> // Для vector.
#include <climits> // Для INT_MIN.
#include "array.h"

using namespace std;

// Функция для чтения из файла.

bool readFile(const string& filename, int& n, int*& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: файл не открыт!" << endl;
        return false;
    }

    file >> n;
    if (n <= 0) {
        cout << "Ошибка: размер <= 0!" << endl;
        return false;
    }

    data = new int[n];
    for (int i = 0; i < n; i++)
        file >> data[i];

    file.close();
    return true;
}

// Задание 4.

void task4(const string& filename) {
    int n = 0;
    int* data = nullptr;
    if (!readFile(filename, n, data)) return;

    Array arr(n);
    arr.fillFrom(data);

    int sum = 0;
    for (int i = 0; i < arr.getSize(); i++)
        sum += arr.get(i);

    int count = 0;
    vector<int> indices;
    for (int i = 0; i < arr.getSize(); i++) {
        if (arr.get(i) > sum) {
            count++;
            indices.push_back(i);
        }
    }*/

    /*cout << "Task 4: Количество элементов > суммы (" << sum << "): " << count << endl;
    if (count > 0) {
        cout << "Номера (от 0): ";
        for (size_t j = 0; j < indices.size(); j++) {
            cout << indices[j];
            if (j < indices.size() - 1) cout << ", ";
        }
        cout << endl;
    }*/

    /*cout << "Task 4: Количество элементов > суммы (" << sum << "): " << count;
    if (count > 0) {
        cout << endl;
        cout << "Номера (от 0): ";
        for (size_t j = 0; j < indices.size(); ++j) {
            if (j) cout << ", ";
            cout << indices[j];
        }
        cout << endl;
    }
    else {
        cout << ";";
    }

    delete[] data; // Очистка памяти.
}

// Задание 5.

void task5(const string& filename) {
    int n = 0;
    int* data = nullptr;
    if (!readFile(filename, n, data)) return;

    Array arr(n);
    arr.fillFrom(data);

    if (n < 5) {
        cout << "Task 5: Массив слишком маленький!" << endl;
        delete[] data;
        return;
    }

    int maxSum = INT_MIN;
    int startIndex = 0;
    for (int i = 0; i <= n - 5; i++) {
        int curSum = arr.get(i) + arr.get(i + 1) + arr.get(i + 2) + arr.get(i + 3) + arr.get(i + 4);
        if (curSum > maxSum) {
            maxSum = curSum;
            startIndex = i;
        }
    }

    cout << "Task 5: Максимальная сумма 5 соседних: " << maxSum << endl;
    cout << "Элементы: ";
    for (int j = startIndex; j < startIndex + 5; j++) {
        cout << arr.get(j);
        if (j < startIndex + 4) cout << ", ";
    }
    cout << endl;

    delete[] data;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        cout << "Ошибка: укажите файл!" << endl;
        return 1;
    }
    string filename = argv[1];

    task4(filename);
    task5(filename);

    return 0;
}*/


#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include "../LibraryCPP/array.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

static bool readFile(const string& filename, int& n, int*& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: файл не открыт!" << endl;
        return false;
    }
    if (!(file >> n) || n <= 0) {
        cout << "Ошибка: размер <= 0!" << endl;
        return false;
    }
    data = new int[n];
    for (int i = 0; i < n; i++) file >> data[i];
    return true;
}

static void task4(const string& filename) {
    int n = 0; int* data = nullptr;
    if (!readFile(filename, n, data)) return;

    Array* arr = array_create(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) array_set(arr, static_cast<size_t>(i), data[i]);

    long long sum = 0;
    for (size_t i = 0; i < array_size(arr); ++i) sum += array_get(arr, i);

    int count = 0;
    vector<int> indices;
    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) > sum) { ++count; indices.push_back(static_cast<int>(i)); }
    }

    cout << "Task 4: Количество элементов > суммы (" << sum << "): " << count;
    if (count > 0) {
        cout << endl;
        cout << "Номера (от 0): ";
        for (size_t j = 0; j < indices.size(); ++j) {
            if (j) cout << ", ";
            cout << indices[j];
        }
        cout << endl;
    }
    else {
        cout << ";";
    }

    array_delete(arr);
    delete[] data;
}

static void task5(const string& filename) {
    int n = 0; int* data = nullptr;
    if (!readFile(filename, n, data)) return;

    Array* arr = array_create(static_cast<size_t>(n));
    for (int i = 0; i < n; ++i) array_set(arr, static_cast<size_t>(i), data[i]);

    if (n < 5) {
        cout << "Task 5: Массив слишком маленький!" << endl;
        array_delete(arr);
        delete[] data;
        return;
    }

    int maxSum = INT_MIN;
    int startIndex = 0;
    for (int i = 0; i <= n - 5; i++) {
        int cur = array_get(arr, i) + array_get(arr, i + 1)
            + array_get(arr, i + 2) + array_get(arr, i + 3)
            + array_get(arr, i + 4);
        if (cur > maxSum) { maxSum = cur; startIndex = i; }
    }

    cout << "Task 5: Максимальная сумма 5 соседних: " << maxSum << endl;
    cout << "Элементы: ";
    for (int j = startIndex; j < startIndex + 5; j++) {
        if (j > startIndex) cout << ", ";
        cout << array_get(arr, j);
    }
    cout << endl;

    array_delete(arr);
    delete[] data;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russia");

    if (argc < 2) {
        cout << "Ошибка: укажите файл!" << endl;
        return 1;
    }
    string filename = argv[1];
    task4(filename);
    task5(filename);
    return 0;
}