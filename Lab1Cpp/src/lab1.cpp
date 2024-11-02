#include "array.h"
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
    int array_element;
    int result = 0;

    for (int i = 0; i < static_cast<int>(array_size(arr)); i++) {
        array_element = array_get(arr, i);
        if (array_element <= 20) {
            result += array_element;
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
        if (count_nums.count(array_element) == 0) {
            count_nums[array_element] = 0;
        }
    }

    for (int i = 0; i < static_cast<int>(array_size(arr)); i++) {
        array_element = array_get(arr, i);
        count_nums[array_element]++;
    }

    for (int i = 0; i < static_cast<int>(array_size(arr)); i++) {
        array_element = array_get(arr, i);
        if (result_value < count_nums[array_element]) {
            result = array_element;
            result_value = count_nums[array_element];
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

    *input >> size;

    srand(static_cast<unsigned int>(time(NULL)));
    Array *arr = array_create_and_read(output, size);
    task1(output, arr);
    *output << "-------------------------" << endl;
    arr = array_create_and_read(output, size);
    task2(output, arr);
    array_delete(arr);
}
