#include <iostream>
#include <random>
#include <limits>
#include <unordered_map>
#include "../LibraryCPP/array.h"

using namespace std;

void fillRandom(Array* arr, int minVal, int maxVal) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minVal, maxVal);

    for (size_t i = 0; i < array_size(arr); ++i) {
        array_set(arr, i, distrib(gen));
    }
}
Data findMaxEvenIndex(const Array* arr) {
    size_t size = array_size(arr);

    std::cerr << "findMaxEvenIndex: size = " << size << std::endl;

    if (size == 0) {
        std::cerr << "findMaxEvenIndex: Array is empty, returning min!!!!!" << std::endl;
        return numeric_limits<Data>::min();
    }

    Data maxVal = numeric_limits<Data>::min();

    for (size_t i = 0; i < size; i += 2) {
        Data val = array_get(arr, i);
        if (val > maxVal) {
            maxVal = val;
        }
    }

    return maxVal;
}
Data findMostFrequent(const Array* arr) {
    size_t size = array_size(arr);

    if (size == 0) {
        std::cerr << "findMostFrequent: Array is empty, returning 0" << std::endl;
        return 0;
    }

    unordered_map<Data, int> counts;

    for (size_t i = 0; i < size; ++i) {
        counts[array_get(arr, i)]++;
    }

    Data mostFrequent = array_get(arr, 0);

    int maxCount = 0;

    for (const auto& pair : counts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequent = pair.first;
        }
    }

    return mostFrequent;
}

int main() {

    // 1.

    size_t size1;
    cin >> size1;
    std::cerr << "main: size1 = " << size1 << std::endl;

    Array* arr1 = array_create(size1);

    if (size1 > 0) {
        fillRandom(arr1, 1, 100);
    }
    else {
        std::cerr << "main: size1 is 0, not filling the array" << std::endl;
    }

    Data maxEven = findMaxEvenIndex(arr1);
    cout << maxEven << endl;

    array_delete(arr1);


    // 2.

    size_t size2;
    cin >> size2;
    std::cerr << "main: size2 = " << size2 << std::endl;

    Array* arr2 = array_create(size2);

    fillRandom(arr2, 1, 10);

    Data mostFrequent = findMostFrequent(arr2);
    cout << mostFrequent << endl;

    array_delete(arr2);

    return 0;
}