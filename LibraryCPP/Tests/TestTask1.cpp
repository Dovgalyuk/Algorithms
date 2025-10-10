//
// Created by Mukhammadzakhid Nematzhanov on 11/10/25.
//

#include <iostream>
#include "../task1.h"
using namespace std;

int main() {
    int arr[] = {1, 3, 5, 2, 7, 9};
    int n = 6;

    int result = task1(arr, n);
    int expected = 3;

    if (result == expected) {
        cout << "Тест task1 прошёл успешно. Результат: " << result << endl;
        return 0;
    } else {
        cerr << "Ошибка в task1. Ожидалось: " << expected << ", получено: " << result << endl;
        return 1;
    }
}
