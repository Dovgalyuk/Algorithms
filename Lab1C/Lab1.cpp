#include <iostream>
#include "../LibraryCPP/array.h"
#include <fstream>

using namespace std;

void fillFibonacci(Array* arr);
void compressArray(Array* arr, int a, int b);
void printArray(const Array* arr);

int main() {
    //Fibonachi
    ifstream file1("input1.txt");
    if (!file1) {
        cerr << "Cannot open input1.txt\n";
        return 1;
    }

    size_t n1;
    file1 >> n1;
    Array* fibArr = array_create(n1);

    fillFibonacci(fibArr);
    printArray(fibArr);

    //Compressed array
    ifstream file2("input2.txt");
    if (!file2) {
        cerr << "Cannot open input2.txt\n";
        array_delete(fibArr);
        return 1;
    }

    size_t n2;
    file2 >> n2;
    Array* compressArr = array_create(n2);

    for (size_t i = 0; i < n2; ++i) {
        Data value;
        if (!(file2 >> value)) {
            cerr << "Invalid data in input2.txt\n";
            array_delete(fibArr);
            array_delete(compressArr);
            return 1;
        }
        array_set(compressArr, i, value);
    }

    int a, b;
    if (!(file2 >> a >> b)) {
        cerr << "Invalid interval data in input2.txt\n";
        array_delete(fibArr);
        array_delete(compressArr);
        return 1;
    }

    compressArray(compressArr, a, b);
    printArray(compressArr);

    //Free memory
    array_delete(fibArr);
    array_delete(compressArr);

	return 0;
}

void fillFibonacci(Array* arr) {
    size_t size = array_size(arr);
    if (size > 0) array_set(arr, 0, 0);
    if (size > 1) array_set(arr, 1, 1);
    for (size_t i = 2; i < size; ++i) {
        Data prev1 = array_get(arr, i - 1);
        Data prev2 = array_get(arr, i - 2);
        array_set(arr, i, prev1 + prev2);
    }
}

void compressArray(Array* arr, int a, int b) {
    size_t size = array_size(arr);
    size_t insertIndex = 0;

    for (size_t i = 0; i < size; ++i) {
        Data current = array_get(arr, i);
        if (current < a || current > b) {
            array_set(arr, insertIndex, current);
            insertIndex++;
        }
    }

    for (size_t i = insertIndex; i < size; ++i) {
        array_set(arr, i, 0);
    }
}

void printArray(const Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
}

