#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "../LibraryCPP/array.h"

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

void test_task1(int result){
    if (result == 10){
        cout << "the test 1 is completed\n";
    }
    else {
        cout << "the test 1 was not completed\n";
    }
}

void task1(Array* arr) {
    test_task1(array_size(arr));
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
    cout << "the number of multiples 2-9: " << count << endl;
}

void test_task2(int result){
    if (result == 6){
        cout << "the test 2 is completed\n";
    }
    else {
        cout << "the test 2 was not completed\n";
    }
}

void task2(Array* arr) {
    test_task2(array_size(arr));
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
            cout << "no minimum difference\n";
        } else {
            cout << "the minimum difference: " << min_diff << endl;
        }
    } else {
        cout << "there are no pairs of even numbers\n";
    }
}

int main() {
    Array* arr1 = array_create_and_read_from_file("input_1.txt");
    if (arr1) {
        task1(arr1);
        array_delete(arr1);
    }

    Array* arr2 = array_create_and_read_from_file("input_2.txt");
    if (arr2) {
        task2(arr2);
        array_delete(arr2);
    }

    return 0;
}
