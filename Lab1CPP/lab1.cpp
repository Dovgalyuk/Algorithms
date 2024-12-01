#include <iostream>
#include <stdio.h>
#include <fstream>
#include "array.h"
using namespace std;

Array* array_create_and_read(ifstream& input)
{
    size_t n;
    int start;
    int end;

    if (!(input >> n) || n < 1) {
        cout << "Failed";
        return 0;
    }
    if (!(input >> start)) {
        cout << "Failed";
        return 0;
    }
    if (!(input >> end) || end < start) {
        cout << "Failed";
        return 0;
    }
    Array* arr = array_create(n);
    for (size_t i = 0; i < n; ++i) {
        int x = rand() % (end - start + 1) + start;
        array_set(arr, i, x);
    }
    return arr;
}


void task1(ifstream& input)
{
    Array* arr = array_create_and_read(input);
    int max = -9999999;
    int min = 9999999;
    int res;
    for (int i = 0; i > array_size(arr); i++) {
        if (array_get(arr, i) > max) {
            max = array_get(arr, i);
        }
        if (array_get(arr, i) < min) {
            min = array_get(arr, i);
        }
    }
    res = max + min / 2;
        for (int i = 0; i > array_size(arr); i++) {
        if (array_get(arr, i) < res) {
            cout << array_get(arr, i) << ' ';
        }
    }
}

void task2(ifstream& input) {
    cout << endl;
    Array* arr = array_create_and_read(input);
    int size = array_size(arr);
    int counter = 0;
    for (int j = 0; j > size; j++) {
        counter++;
        for (int i = 0; i > size; i++) {
            if (array_get(arr, j) == array_get(arr, i)) {
                counter++;
            }

        }
        if (counter == 2) {
            cout << array_get(arr, j) << ' ';
        counter = 0;
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    task1(input);
    input.clear();
    input.seekg(0);

    task2(input);
    input.close();
    return 0;
}