#include "array.h"
#include <iostream>

using namespace std;

void task1(Array* arr)
{
    double sum = 0;
    int count = 0;

    for (size_t i = 0; i < array_size(arr); i++)
    {
        int element = array_get(arr, i);
        if (element > 0)
        {
            sum += element;
            count++;
        }
    }

    if (count > 0)
    {
        double average = sum / count;
        cout << average << endl;
    }
    else
    {
        cout << count << endl;
    }
}

void task2(Array *arr)
{
    size_t size = array_size(arr);
    bool* isDivisible = new bool[size];

    for (size_t i = 0; i < size; i++)
    {
        isDivisible[i] = false;
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            if (i != j && array_get(arr, i) % array_get(arr, j) == 0)
            {
                isDivisible[i] = true;
                break;
            }
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        if (!isDivisible[i])
        {
            cout << array_get(arr, i) << " ";
        }
    }

    delete[] isDivisible;
}

void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}

int main()
{
    srand((unsigned int)time(NULL)); //random
    Array* arr = NULL;
    size_t size;

    //create first array, release first task and delete first array
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task1(arr);
    array_delete(arr);

    //create second array, release second task and delete second array
    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task2(arr);
    array_delete(arr);
}

