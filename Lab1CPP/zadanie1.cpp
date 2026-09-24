#include <fstream>
#include <iostream>
#include "array.h"
using namespace std;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Не указан входной файл\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input.is_open()) {
        cout << "Не удалось открыть файл\n";
        return 1;
    }

    int n;

    if (!(input >> n) || n < 0) {
        cout << "Некорректный размер массива\n";
        return 1;
    }

    Array* arr = array_create(n);

    int remainder = 1;

    for (size_t i = 0; i < array_size(arr); ++i) {
        remainder *= 10;

        array_set(arr, i, remainder / 17);

        remainder %= 17;
    }

    for (size_t i = 0; i < array_size(arr); ++i) {
        cout << array_get(arr, i) << " ";
    }

    cout << '\n';
    array_delete(arr);
    return 0;
}