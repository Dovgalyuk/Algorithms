#include "../LibraryCPP/array.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

int random(int start, int end) {
    return rand() % (end - start + 1) + start;
}

Array* array_create_and_read(ostream *output, int size) {
    int random_result;

    Array *arr = array_create(size);

    *output << "Array: [";

    for (int i = 0; i < size; i++) {
        random_result = random(1, 100);
        array_set(arr, i, random_result);
        *output << random_result;
        if (i != size - 1) {
            *output << ", ";
        }
    }
    *output << ']' << endl;

    return arr;
}

void task1(ostream* output, Array *arr)
{
    int result = 0;

    for (int i = 0; i < static_cast<int>(array_size(arr)); i++) {
        int array_element = array_get(arr, i);
        
        while (array_element > 0) {
            result += array_element % 10;
            array_element /= 10;          
        }
    }

    *output << "Task1: " << result << endl;
}


void task2(ostream* output, Array *arr)
{
    int array_element;
    int result = -1;
    int result_value = 0;
    map<int, int> count_nums;

    for (int i = 0; i < static_cast<int>(array_size(arr)); i++) {
        array_element = array_get(arr, i);
        count_nums[array_element]++;
    }

    for (const auto& pair : count_nums) {
        if (pair.second > result_value) {
            result = pair.first;
            result_value = pair.second;
        }
    }

    *output << "Task2: " << result;
}

int main(int argc, char* argv[])
{
    istream* input = &cin;
    ostream* output = &cout;
    ifstream inputFile;
    ofstream outputFile;
    int size;

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

    if (*input >> size) {
        if (size <= 0 || size > 10000) {
            cerr << "Invalid or too large array size!" << endl;
            return 1;
        }
    } else {
        cerr << "Failed to read size! Please check the input file format." << endl;
        return 1;
    }

    srand(static_cast<unsigned int>(time(NULL)));
    Array *arr = array_create_and_read(output, size);
    task1(output, arr);
    *output << "-------------------------" << endl;
    array_delete(arr);
    arr = array_create_and_read(output, size);
    task2(output, arr);
    array_delete(arr);

    return 0;
}