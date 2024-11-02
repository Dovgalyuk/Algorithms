#include <stdio.h>
#include <fstream>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

int random(int start, int end) {
    return rand() % (end - start + 1) + start;
}

Array* array_create_and_read()
{
    ifstream file("input.txt");

    if (!file.is_open()) {
        cerr << "Error: Could not open file 'input.txt'" << endl;
        return nullptr;
    }

    int num;
    int random_result;
    file >> num;

    Array *arr = array_create(num);

    cout << "Array: [";

    for (int i = 0; i < num; i++) {
        random_result = random(1, 100);
        array_set(arr, i, random_result);
        cout << random_result;
        if (i != num - 1) {
            cout << ", ";
        }
    }
    cout << ']' << endl;

    return arr;
}

void task1(Array *arr)
{
    int array_element;
    int result = 0;

    for (int i = 0; i < array_size(arr); i++) {
        array_element = array_get(arr, i);
        if (array_element <= 20) {
            result += array_element;
        }
    }

    cout << "Task1: " << result << endl;
}

void task2(Array *arr)
{
    int array_element;
    int result = -1;
    int result_value = 0;
    map<int, int> count_nums;
    
    for (int i = 0; i < array_size(arr); i++) {
        array_element = array_get(arr, i);
        if (count_nums.count(array_element) == 0) {
            count_nums[array_element] = 0;
        }
    }

    for (int i = 0; i < array_size(arr); i++) {
        array_element = array_get(arr, i);
        count_nums[array_element]++;
    }

    for (int i = 0; i < array_size(arr); i++) {
        array_element = array_get(arr, i);
        if (result_value < count_nums[array_element]) {
            result = array_element;
            result_value = count_nums[array_element];
        }
    }

    cout << "Task2: " << result;
}

int main(int argc, char **argv)
{
    srand(static_cast<unsigned int>(time(NULL)));
    Array *arr = array_create_and_read();
    task1(arr);
    arr = array_create_and_read();
    task2(arr);
}
