#include <iostream>
#include "array.h"
#include <fstream>
#include <sstream>

#include "../LibraryCPPClass/array.h"

Array *read_file_and_create_array(std::ifstream &file) {
    size_t count;
    file >> count;

    Array *arr = array_create(count);

    std::string dummy;
    std::getline(file, dummy);

    std::string line;

    while (std::getline(file,line)) {
        std::stringstream ss(line);
        int number;
        size_t i = 0;

        while (i < count) {
            ss >> number;
            array_set(arr, i, number);
            i++;
        }
    }

    return arr;
}

int main() {
    std::ifstream input("input.txt");

    Array *arr = read_file_and_create_array(input);

    std::cout << array_get(arr, 2) << '\n';

    array_delete(arr);
    return 0;
}