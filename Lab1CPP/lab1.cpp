#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

Array* array_create_and_write(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr) 
{
    if (arr == nullptr)
        return;

    size_t size = array_size(arr);
    size_t max_length = 0;
    size_t current_length = 0;

    for (size_t i = 0; i < size; i++) {
        int value = array_get(arr, i);
        if (value % 2 != 0) {
            current_length++;
        }
        else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    cout << max_length << endl;
}

void task2(Array *arr) 
{
    size_t size = array_size(arr);
    if (size < 5) {
        return;
    }

    int max_sum = 0;
    size_t max_index = 0;

    for (size_t j = 0; j < 5; j++) {
        max_sum += array_get(arr, j);
    }

    for (size_t i = 1; i <= size - 5; i++) {
        int current_sum = 0;
        for (size_t j = 0; j < 5; j++) {
            current_sum += array_get(arr, i + j);
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            max_index = i;
        }
    }

    for (size_t i = 0; i < 5; i++) {
        cout << array_get(arr, max_index + i);
        if (i < 4) cout << " ";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }
    
    ifstream input(argv[1]);;

    Array *arr = array_create_and_write(input);

    task1(arr);
    array_delete(arr);

    /* Create another array here */
    arr = array_create_and_write(input);

    task2(arr);
    array_delete(arr);
    input.close();
}