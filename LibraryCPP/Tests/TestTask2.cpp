//
// Created by Mukhammadzakhid Nematzhanov on 11/10/25.
//
#include <iostream>
#include "../task2.h"
using namespace std;

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    int a = 2, b = 4;

    task2(arr, n, a, b);

    int expected[] = {1, 5, 0, 0, 0};
    bool correct = true;

    for (int i = 0; i < n; i++) {
        if (arr[i] != expected[i]) {
            correct = false;
            cerr << "Ошибка в task2: элемент [" << i << "] — ожидалось " << expected[i] << ", получено " << arr[i] << endl;
            break;
        }
    }

    if (correct) {
        cout << "Тест task2 прошёл успешно." << endl;
        return 0;
    } else {
        return 1;
    }
}
