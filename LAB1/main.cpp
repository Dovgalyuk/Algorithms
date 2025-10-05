#include <iostream>
#include <fstream>
#include "Function.h"
using namespace std;

int main() {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл!" << endl;
        return 1;
    }

    int n;
    file >> n;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }

    int a, b;
    file >> a >> b;
cout << "размер массива " << n << endl;
    cout << "элементы массива " ;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "интервал " << a << " " << b << endl;

    int maxLen = maxOddSegment(arr, n);
    cout << "Максимальная длина отрезка нечетных чисел: " << maxLen << endl;

    compressArray(arr, n, a, b);

    cout << "Сжатый массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    file.close();
    return 0;
}
