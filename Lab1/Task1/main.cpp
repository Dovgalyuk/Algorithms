#include <iostream>
#include <fstream>
#include <cstdlib>
#include "array.h"
using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    if (argc < 2) {
        cout << "Не указан входной файл";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input) {
        cout << "Ошибка открытия файла";
        return 1;
    }

    int n;

    if (!(input >> n)) {
        cout << "Ошибка чтения файла";
        return 1;
    }

    if (n <= 0) {
        cout << "Некорректный размер массива";
        return 1;
    }
    
    Array arr(n);
    for (int i = 0; i < n; i++) {
        int value;

        if (!(input >> value)) {
            cout << "Во входном файле недостаточно элементов";
            return 1;
        }

        arr.set(i, value);
    }

    int max = arr.get(0);
    for (int i = 1; i < n; i++) {
        if (max < arr.get(i)) {
            max = arr.get(i);
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (max < abs(arr.get(i))) {
            count++;
        }
    }

    cout << count;

    return 0;
}