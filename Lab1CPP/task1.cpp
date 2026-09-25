#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

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
    long long totalSum = 0;

    for (size_t i = 0; i < arrSize; i++) {
        Data val = 0;
        if (!(inputFile >> val)) {
            cerr << "Error reading data" << endl;
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, val);
        totalSum += val;
    }

    size_t foundCount = 0;
    for (size_t i = 0; i < arrSize; i++) {
        if (array_get(arr, i) > totalSum) {
            foundCount++;
        }
    }

    cout << foundCount << endl;

    if (foundCount > 0) {
        Array* resultArr = array_create(foundCount);
        size_t targetIdx = 0;

        for (size_t i = 0; i < arrSize; i++) {
            if (array_get(arr, i) > totalSum) {
                array_set(resultArr, targetIdx, (Data)i);
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