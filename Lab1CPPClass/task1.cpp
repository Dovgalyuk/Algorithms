#include <cstdlib>
#include <fstream>
#include <iostream>

#include "common.h"

using namespace std;

// Выводит в первой строке индексы элементов массива, которые больше суммы всех элементов массива, через пробел
// Если таких элементов нет, то выводит пустую строку
// Во второй строке выводит количество таких элементов
void task1(Array* arr) {
    long long sum = 0;
    for (size_t i = 0; i < arr->size(); ++i) {
        sum += arr->get(i);
    }

    int cnt = 0;
    bool first = true;
    for (size_t i = 0; i < arr->size(); ++i) {
        if (arr->get(i) > sum) {
            if (!first) {
                cout << " ";
            }
            first = false;
            cout << i;
            ++cnt;
        }
    }
    cout << "\n" << cnt << endl;
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

    task1(arr);
    delete arr;

    return EXIT_SUCCESS;
}