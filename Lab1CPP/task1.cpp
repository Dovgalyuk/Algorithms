#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    string filename = "input1.txt";
    if (argc > 1) {
        filename = argv[1];
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    int n;
    file >> n;

    Array* arr = array_create(n);
    for (int i = 0; i < n; i++) {
        int val;
        file >> val;
        array_set(arr, i, val);
    }
    file.close();

    // Разворот на месте без второго массива
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int temp = array_get(arr, left);
        array_set(arr, left, array_get(arr, right));
        array_set(arr, right, temp);
        left++;
        right--;
    }

    cout << "Перевернутый массив: ";
    for (int i = 0; i < n; i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    array_delete(arr);
    return 0;
}
