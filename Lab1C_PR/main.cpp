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
    }

    cout << "Task 4: Количество элементов > суммы (" << sum << "): " << count << endl;
    if (count > 0) {
        cout << "Номера (от 0): ";
        for (size_t j = 0; j < indices.size(); j++) {
            cout << indices[j];
            if (j < indices.size() - 1) cout << ", ";
        }
        cout << endl;
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
#include "array.h"
#include <queue.h>

using namespace std;

bool readFile(const string& filename, size_t& n, Data*& data) {
    ifstream file(filename);
    if (!file.is_open()) { cout << "File not opened" << endl; return false; }
    file >> n;
    if (n <= 0) { cout << "Size <=0" << endl; return false; }
    data = new Data[n];
    for (size_t i = 0; i < n; i++) file >> data[i];
    file.close();
    return true;
}

void task4(const string& filename) {
    size_t n = 0;
    Data* data = nullptr;
    if (!readFile(filename, n, data)) return;
    Array arr(n);
    for (size_t i = 0; i < n; i++) arr.set(i, data[i]);
    Data sum = 0;
    for (size_t i = 0; i < arr.getSize(); i++) sum += arr.get(i);
    int count = 0;
    vector<size_t> indices;
    for (size_t i = 0; i < arr.getSize(); i++) {
        if (arr.get(i) > sum) { count++; indices.push_back(i); }
    }
    cout << "Task 4: count > sum (" << sum << "): " << count << endl;
    if (count > 0) { cout << "Indices: "; for (size_t idx : indices) cout << idx << " "; cout << endl; }
    delete[] data;
}

void task5(const string& filename) {
    size_t n = 0;
    Data* data = nullptr;
    if (!readFile(filename, n, data)) return;
    Array arr(n);
    for (size_t i = 0; i < n; i++) arr.set(i, data[i]);
    if (n < 5) { cout << "Task 5: array <5" << endl; delete[] data; return; }
    Data maxSum = INT_MIN;
    size_t start = 0;
    for (size_t i = 0; i <= n - 5; i++) {
        Data cur = arr.get(i) + arr.get(i + 1) + arr.get(i + 2) + arr.get(i + 3) + arr.get(i + 4);
        if (cur > maxSum) { maxSum = cur; start = i; }
    }
    cout << "Task 5: max sum: " << maxSum << endl;
    cout << "Elements: ";
    for (size_t j = start; j < start + 5; j++) cout << arr.get(j) << " ";
    cout << endl;
    delete[] data;
}

int main(int argc, char* argv[]) {
    if (argc < 2) { cout << "Specify file!" << endl; return 1; }
    string filename = argv[1];
    task4(filename);
    task5(filename);
    return 0;
}