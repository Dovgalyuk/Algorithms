#include <iostream>
#include "Array.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Array arr(5);
    for (int i = 0; i < arr.getSize(); i++) {
        arr[i] = (i + 1) * 10;
    }

    cout << "Тест массива: ";
    for (int i = 0; i < arr.getSize(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}