#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <numeric>

using namespace std;

class DynamicArray {
public:
    DynamicArray(size_t size) : size(size), data(new int[size]) {}

    ~DynamicArray() {
        delete[] data;
    }

    size_t getSize() const {
        return size;
    }

    int& operator[](size_t index) {
        return data[index];
    }

    const int& operator[](size_t index) const {
        return data[index];
    }

private:
    size_t size;
    int* data;
};

// Function to process the array and find elements greater than the sum of all elements
vector<int> findElementsGreaterThanSum(const DynamicArray& array) {
    int sum = 0;
    for (size_t i = 0; i < array.getSize(); ++i) {
        sum += array[i];
    }

    vector<int> result;
    for (size_t i = 0; i < array.getSize(); ++i) {
        if (array[i] > sum) {
            result.push_back(array[i]);
        }
    }
    return result;
}

// Function to find elements that occur only once
vector<int> findUniqueElements(const DynamicArray& array) {
    unordered_map<int, int> frequency;

    for (size_t i = 0; i < array.getSize(); ++i) {
        frequency[array[i]]++;
    }

    vector<int> result;
    for (size_t i = 0; i < array.getSize(); ++i) {
        if (frequency[array[i]] == 1) {
            result.push_back(array[i]);
        }
    }
    return result;
}

void writeResultsToFile(const vector<int>& column1, const vector<int>& column2, const string& filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    // Write first column: element greater than sum of array (first element only)
    if (!column1.empty()) {
        outfile << column1[0] << endl;
    }

    // Write second column: unique elements
    for (size_t i = 0; i < column2.size(); ++i) {
        outfile << column2[i] << " ";
    }
    outfile << endl;

    outfile.close();
    cout << "Results written to " << filename << endl;
}

int main() {
    // Part 1: Find elements greater than the sum
    size_t size1;
    cout << "Enter the size of the first array: ";
    cin >> size1;

    DynamicArray array1(size1);
    cout << "Enter " << size1 << " elements for the first array: ";
    for (size_t i = 0; i < size1; ++i) {
        cin >> array1[i];
    }

    vector<int> greaterThanSum = findElementsGreaterThanSum(array1);

    // Part 2: Find unique elements
    size_t size2;
    cout << "Enter the size of the second array: ";
    cin >> size2;

    DynamicArray array2(size2);
    cout << "Enter " << size2 << " elements for the second array: ";
    for (size_t i = 0; i < size2; ++i) {
        cin >> array2[i];
    }

    vector<int> uniqueElements = findUniqueElements(array2);

    // Write results to file
    const string outputFilename = "output.txt";
    writeResultsToFile(greaterThanSum, uniqueElements, outputFilename);

    return 0;
}
