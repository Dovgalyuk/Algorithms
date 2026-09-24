#include <fstream>
#include <iostream>
#include "Array.h"

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

    for (size_t i = 0; i < array_size(arr); ++i) {
        int value;

        if (!(input >> value)) {
            cout << "Не удалось прочитать элемент массива\n";
            array_delete(arr);
            return 1;
        }

        array_set(arr, i, value);
    }

    int a, b;

    if (!(input >> a >> b)) {
        cout << "Не удалось прочитать интервал\n";
        array_delete(arr);
        return 1;
    }

    size_t writeIndex = 0;

    for (size_t readIndex = 0;
        readIndex < array_size(arr);
        ++readIndex)
    {
        int value = array_get(arr, readIndex);

        if (value < a || value > b) {
            array_set(arr, writeIndex, value);
            ++writeIndex;
        }
    }

    for (; writeIndex < array_size(arr); ++writeIndex) {
        array_set(arr, writeIndex, 0);
    }

    for (size_t i = 0; i < array_size(arr); ++i) {
        cout << array_get(arr, i) << " ";
    }

    cout << '\n';
    array_delete(arr);

    return 0;
}