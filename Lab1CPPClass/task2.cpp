#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "common.h"

using namespace std;

// Выводит массив arr, сдвинутый на shift позиций
// Если shift > 0, то сдвиг влево, если shift < 0, то сдвиг вправо.
// Освободившиеся элементы заполняются нулями
void task2(Array* arr, long long shift) {
    int n = static_cast<int>(arr->size());

    if (shift > 0) {
        int k = min(static_cast<int>(shift), n);  // нужно, чтобы не выйти за границы массива
        for (int i = n - 1; i >= k; --i) {
            arr->set(i, arr->get(i - k));
        }
        for (int i = 0; i < k; ++i) {
            arr->set(i, 0);
        }
    } else if (shift < 0) {
        int k = min(static_cast<int>(-shift), n);
        for (int i = 0; i < n - k; ++i) {
            arr->set(i, arr->get(i + k));
        }
        for (int i = n - k; i < n; ++i) {
            arr->set(i, 0);
        }
    }

    for (size_t i = 0; i < arr->size(); ++i) {
        cout << arr->get(i) << (i + 1 == arr->size() ? '\n' : ' ');
    }
}

int main(int argc, char** argv) {
    const char* filename = (argc > 1) ? argv[1] : "input.txt";

    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Unable to open file \"" << filename << "\"\n";
        return EXIT_FAILURE;
    }

    Array* arr = array_create_and_read(inFile);
    if (!arr) {
        cerr << "Failed to read array from file \"" << filename << "\"\n";
        return EXIT_FAILURE;
    }

    long long shift;
    if (!(inFile >> shift)) {
        cerr << "Failed to read shift value from file \"" << filename << "\"\n";
        delete arr;
        return EXIT_FAILURE;
    }

    task2(arr, shift);
    delete arr;

    return EXIT_SUCCESS;
}
