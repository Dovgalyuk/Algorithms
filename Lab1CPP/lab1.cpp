#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "array.h"

using namespace std;

Array* array_create_and_read_from_file(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "error: " << filename << endl;
        return nullptr;
    }

    size_t size;
    inputFile >> size;

    Array *arr = array_create(size);
    if (!arr) return nullptr;

    for (size_t i = 0; i < size; ++i) {
        int number;
        if (!(inputFile >> number)) {
            cerr << "error: " << size << endl;
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, number);
    }

    inputFile.close();
    return arr;
}

void task1(Array* arr) {
    int count = 0;
    for (size_t i  = 0; i < array_size(arr); ++i){
        int num = array_get(arr, i);
        for (int j = 2; j <= 9; ++j) {
            if (num % j == 0) {
                count++;
                break;
            }
        }
    }
    cout << "count numbers 2-9: " << count << endl;
}

void task2(Array* arr) {
    int min_diff = -1;
    bool flag = false;

    for (size_t i = 0; i < array_size(arr); ++i) {
        int num = (array_get(arr, i));
        if (num % 2 == 0) {
            flag = true;
            for (size_t j = 0; j < array_size(arr); ++j) {
                if (i != j && (array_get(arr, j)) % 2 == 0) {
                    int diff = fabs(num - (array_get(arr, j)));

                    if (min_diff == -1 || diff < min_diff) {
                        min_diff = diff;
                    }
                }
            }
        }
    }

    if (flag) {
        if (min_diff == -1) {
            cout << "no min_diff\n";
        } else {
            cout << "min_diff: " << min_diff << endl;
        }
    } else {
        cout << "no\n";
    }
}

int main() {
    Array* arr1 = array_create_and_read_from_file("input.txt");
    if (arr1) {
        task1(arr1);
        array_delete(arr1);
    }

    Array* arr2 = array_create_and_read_from_file("input.txt");
    if (arr2) {
        task2(arr2);
        array_delete(arr2);
    }

    return 0;
}
