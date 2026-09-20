#include <iostream>
#include <fstream>
#include "Array.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream file("input1.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл input1.txt" << endl;
        return 1;
    }

    int n;
    file >> n;

    Array arr(n);
    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }
    file.close();

    // Разворот на месте без второго массива
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        left++;
        right--;
    }

    cout << "Перевернутый массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}