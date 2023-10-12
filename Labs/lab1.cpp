#include <stdio.h>
#include "array.h"
#include <iostream>

using namespace std;

void task1(Array* arr)
{
    int sum = 0, index = 0, min_razn;
    for (int i = 0; i < array_size(arr); i++)
    {
		cout << array_get(arr, i) << " ";
        sum += array_get(arr, i);
    }
	cout << endl;
    float srzn = (float)sum / array_size(arr);
    min_razn = abs(array_get(arr, 0) - (int)srzn);
    for (int i = 0; i < array_size(arr); i++)
    {
        if (abs(array_get(arr, i) - srzn) < min_razn)
        {
            min_razn = abs(array_get(arr, i) - (int)srzn);
            index = i;
        }
    }
    cout << "result: " << array_get(arr, index) << endl;
}

void task2(Array* arr)
{
    bool flag = 1;
    for (int i = 0; i < array_size(arr); i++)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
    cout << "result: ";
    for (int i = 0; i < array_size(arr); i++)
    {
        for (int j = 0; j < array_size(arr); j++)
        {
            if (array_get(arr, i) == array_get(arr, j) && i!=j)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            cout << array_get(arr, i) << " ";
        }
    }
}

void createArray(Array* arr)
{
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
    {
        array_set(arr, i, rand());
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    Array* arr = NULL;

    /* Create array here */
    int size;
    cout << "Size array1: ", cin >> size;
    arr = array_create(size);
    createArray(arr);
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    cout << "Size array2: ", cin >> size;
    arr = array_create(size);
    createArray(arr);
    task2(arr);
    array_delete(arr);
}
