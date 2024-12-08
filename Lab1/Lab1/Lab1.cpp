#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <numeric>

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
void findElementsGreaterThanSum(const DynamicArray& array) {
    int sum = 0;
    for (size_t i = 0; i < array.getSize(); ++i) {
        sum += array[i];
    }

    std::cout << "Elements greater than the sum of the array: ";
    for (size_t i = 0; i < array.getSize(); ++i) {
        if (array[i] > sum) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

// Function to find elements that occur only once
void findUniqueElements(const DynamicArray& array) {
    std::unordered_map<int, int> frequency;

    for (size_t i = 0; i < array.getSize(); ++i) {
        frequency[array[i]]++;
    }

    std::cout << "Elements that appear only once: ";
    for (size_t i = 0; i < array.getSize(); ++i) {
        if (frequency[array[i]] == 1) {
            std::cout << array[i] << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    // Default file name
    const std::string filename = "arr.txt";

    // Open file to determine size and read data
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return 1;
    }

    std::vector<int> tempArray;
    int value;
    while (infile >> value) {
        tempArray.push_back(value);
    }
    infile.close();

    size_t size = tempArray.size();
    DynamicArray array(size);
    for (size_t i = 0; i < size; ++i) {
        array[i] = tempArray[i];
    }

    // Call functions to process the array
    findElementsGreaterThanSum(array);
    findUniqueElements(array);

    return 0;
}
