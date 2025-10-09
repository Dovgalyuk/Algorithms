#include <stdio.h>
#include "array.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void read_arr(int size, ifstream& input, Array* arr)
{
    int value;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        input >> value;
        array_set(arr, i, value);
    }
}

void task1(ifstream& input)
{
    int size;
    input >> size;
    Array* arr = array_create(size);

    read_arr(size, input, arr);

    int pos = 0, neg = 0, zer = 0;
    for (size_t i = 0; i < array_size(arr); i++)
    {
        if (array_get(arr, i) > 0)
        {
            pos++;
        }
        else if (array_get(arr, i) < 0)
        {
            neg++;
        }
        else
        {
            zer++;
        }
    }

    cout << pos << " " << neg << " " << zer << "\n";
    array_delete(arr);
}

void task2(ifstream& input)
{
    int size;
    input >> size;
    Array* arr = array_create(size);

    read_arr(size, input, arr);

    int maxSum = 0, left = 0, sum;

    for (int j = 0; j < 5; j++)
    {
        maxSum += array_get(arr, j);
    }
    sum = maxSum;

    for (int i = 0; i < size - 5; i++)
    {
        sum -= array_get(arr, i);
        sum += array_get(arr, i + 5);
        if (sum > maxSum)
        {
            maxSum = sum;
            left = i + 1;
        }
    }

    cout << "maxSum: " << maxSum << "\n";
    cout << "Array: ";
    for (int i = left; i < left + 5; i++)
    {
        cout << array_get(arr, i) << " ";
    }
    array_delete(arr);
}

int main(int argc, char* argv[]) {
    ifstream input;
    string name;
    if (argc > 1) {
        name = argv[1];
    }
    input.open(name);
    task1(input);
    task2(input);
    input.close();
    return 0;
}