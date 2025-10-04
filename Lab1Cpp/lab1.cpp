#include <stdio.h>
#include "array.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void task1(ifstream& input)
{
    int size;
    input >> size;
    Array* arr = array_create(size);

    int value;
    for (int i = 0; i < size; i++)
    {
        input >> value;
        array_set(arr, i, value);
    }

    int pos = 0, neg = 0, zer = 0;
    for (int i = 0; i < array_size(arr); i++)
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

    int value;
    for (int i = 0; i < size; i++)
    {
        input >> value;
        array_set(arr, i, value);
    }

    int maxSum = -1, left = 0;
    for (int i = 0; i <= size - 5; i++)
    {
        int sum = 0;
        for (int j = i; j < i + 5; j++)
        {
            sum += array_get(arr, j);
        }
        if (sum > maxSum)
        {
            maxSum = sum;
            left = i;
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

int main() {
    ifstream input;
    input.open("input.txt");
    task1(input);
    task2(input);
    input.close();
    return 0;
}