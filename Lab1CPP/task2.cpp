#include <iostream>
#include <fstream>
#include "Array.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    ifstream file("input2.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл input2.txt" << endl;
        return 1;
    }

    int n;
    file >> n;

    Array arr(n);
    int counts[1001] = {0};

    // Заполнение и подсчет за один проход O(N)
    for (int i = 0; i < n; i++) {
        file >> arr[i];
        if (arr[i] >= 0 && arr[i] <= 1000) {
            counts[arr[i]]++;
        }
    }
    file.close();

    cout << "Числа, встречающиеся ровно 2 раза: ";
    for (int val = 0; val <= 1000; val++) {
        if (counts[val] == 2) {
            cout << val << " ";
        }
    }
    cout << endl;

    return 0;
}