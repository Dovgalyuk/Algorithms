#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

bool isDivisibleByOthers(const Array* arr, size_t index, size_t arrSize)
{
    Data current = array_get(arr, index);

    for (size_t j = 0; j < arrSize; j++) {
        if (j == index) {
            continue;
        }

        Data other = array_get(arr, j);
        if (other != 0 && other != current && current % other == 0) {
            return true;
        }
    }

    return false;
}

int main(int argc, char* argv[])
{
    ifstream inputFile;
    if (argc > 1) {
        inputFile.open(argv[1]);
    }
    else {
        string fileName;
        cin >> fileName;
        inputFile.open(fileName);
    }

    if (!inputFile.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    size_t arrSize = 0;
    if (!(inputFile >> arrSize) || arrSize == 0) {
        return 1;
    }

    Array* arr = array_create(arrSize);
    for (size_t i = 0; i < arrSize; i++) {
        Data val = 0;
        if (!(inputFile >> val)) {
            cerr << "Error reading data" << endl;
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, val);
    }

    size_t foundCount = 0;
    for (size_t i = 0; i < arrSize; i++) {
        if (!isDivisibleByOthers(arr, i, arrSize)) {
            foundCount++;
        }
    }

    if (foundCount > 0) {
        Array* resultArr = array_create(foundCount);
        size_t targetIdx = 0;

        for (size_t i = 0; i < arrSize; i++) {
            if (!isDivisibleByOthers(arr, i, arrSize)) {
                array_set(resultArr, targetIdx, array_get(arr, i));
                targetIdx++;
            }
        }

        for (size_t i = 0; i < foundCount; i++) {
            cout << array_get(resultArr, i) << " ";
        }
        cout << endl;

        array_delete(resultArr);
    }

    array_delete(arr);
    return 0;
}