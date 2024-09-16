#include "../LibraryCPPClass/array.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

void fillArrayWithRandom(Array &arr) {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (size_t i = 0; i < arr.size(); ++i) {
        arr.set(i, rand() % 100);
    }
}

Array Task1_findEvenIndices(const Array &arr) {
    vector<size_t> evenIndices;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr.get(i) % 2 == 0 && arr.get(i) != 0) {
            evenIndices.push_back(i);
        }
    }

    Array evenIndexArray(evenIndices.size());
    for (size_t i = 0; i < evenIndices.size(); ++i) {
        evenIndexArray.set(i, evenIndices[i]);
    }
    return evenIndexArray;
}

vector<int> Task2_findUniqueElements(const Array &arr) {
    vector<int> uniqueElements;
    for (size_t i = 0; i < arr.size(); ++i) {
        int current = arr.get(i);
        size_t count = 0;
        for (size_t j = 0; j < arr.size(); ++j) {
            if (arr.get(j) == current) {
                ++count;
            }
        }
        if (count == 1) {
            uniqueElements.push_back(current);
        }
    }
    return uniqueElements;
}

int main(int argc, char* argv[]) {
    istream* input = &cin;
    ostream* output = &cout;
    ifstream inputFile;
    ofstream outputFile;

    if (argc == 3) {
        inputFile.open(argv[1]);
        outputFile.open(argv[2]);

        if (!inputFile || !outputFile) {
            cerr << "Error opening file!\n";
            return 1;
        }

        input = &inputFile;
        output = &outputFile;
    }

    // Задача 1
    *output << "[ EX_1 ] - Indices of even numbers\n";
    cout << "Enter the array size: ";
    int size1;
    *input >> size1;

    Array arr1(size1);
    fillArrayWithRandom(arr1);

    *output << "\n[-RESULT-]\n";
    *output << "Original array: ";
    for (size_t i = 0; i < arr1.size(); ++i) {
        *output << arr1.get(i) << " ";
    }
    *output << endl;

    Array evenIndices = Task1_findEvenIndices(arr1);

    *output << "Indices of even numbers: ";
    for (size_t i = 0; i < evenIndices.size(); ++i) {
        *output << evenIndices.get(i) << " ";
    }
    *output << endl;

    *output << "\n-----------------------------------\n";

    // Задача 2
    *output << "\n[ EX_2 ] - Unique elements\n";
    cout << "Enter the array size: ";
    int size2;
    *input >> size2;

    Array arr2(size2);
    fillArrayWithRandom(arr2);

    *output << "\n[-RESULT-]\n";
    *output << "Original array: ";
    for (size_t i = 0; i < arr2.size(); ++i) {
        *output << arr2.get(i) << " ";
    }
    *output << endl;

    vector<int> uniqueElements = Task2_findUniqueElements(arr2);

    *output << "Unique elements: ";
    for (int element : uniqueElements) {
        *output << element << " ";
    }
    *output << endl;

    return 0;
}
