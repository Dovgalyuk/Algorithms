#include <iostream>
#include <fstream>
#include  <../LibraryCPP/task1.h>
#include  <../LibraryCPP/task2.h>
#include "../LibraryCPP/array.h"

using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    int n;
    file >> n;
    Array* arr = array_create(n);

    for (int i = 0; i < n; i++) {
        int x;
        file >> x;
        array_set(arr, i, x);
    }

    int a, b;
    file >> a >> b;

    cout << "размер массива " << n << endl;
    cout << "элементы массива ";
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    cout << "интервал " << a << " " << b << endl;

    size_t maxLen = task1(arr);
    cout << "Максимальная длина отрезка нечетных чисел: " << maxLen << endl;

    task2(arr, a, b);

    cout << "Сжатый массив: ";
    for (int i = 0; i < n; i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    array_delete(arr);
    file.close();
    return 0;
}
