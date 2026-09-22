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
    int counts[1001] = {0};

    // Чтение, сохранение в массив LibraryCPP и подсчет частоты
    for (int i = 0; i < n; i++) {
        int val;
        file >> val;
        array_set(arr, i, val);
        if (val >= 0 && val <= 1000) {
            counts[val]++;
        }
    }
    file.close();

    // Вывод чисел, встречающихся ровно 2 раза
    for (int val = 0; val <= 1000; val++) {
        if (counts[val] == 2) {
            cout << val << " ";
        }
    }
    cout << endl;

    array_delete(arr);
    return 0;
}
