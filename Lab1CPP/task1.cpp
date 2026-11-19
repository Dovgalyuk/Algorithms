#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
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

    // Разворот на месте двумя указателями
    int left = 0;
    int right = n - 1;
    while (left < right) {
        int temp = array_get(arr, left);
        array_set(arr, left, array_get(arr, right));
        array_set(arr, right, temp);
        left++;
        right--;
    }

    // Вывод развернутого массива
    for (int i = 0; i < n; i++) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;

    array_delete(arr);
    return 0;
}
