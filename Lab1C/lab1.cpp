#include <iostream>
#include "array.h"

using namespace std;

void RandArr(Array* arr)
{
    for (int index = 0; index < array_size(arr); index++)
    {
        array_set(arr, index, rand() % 100);
    }
}

void task1(Array* arr)
{
    RandArr(arr);

    int count = 0;
    float middle;
    int minArrMember = 101, maxArrMember = -1;

    for (size_t index = 0; index < array_size(arr); index++)
    {
        if (array_get(arr, index) < minArrMember)
            minArrMember = array_get(arr, index);

        if (array_get(arr, index) > maxArrMember)
            maxArrMember = array_get(arr, index);
    }

    middle = float((maxArrMember + minArrMember) / 2);
    
    for (size_t index = 0; index < array_size(arr); index++)
    {
        if (array_get(arr, index) > middle)
        {
            count++;
            cout << index << " ";
        }
    }
    cout << endl;
}

void task2(Array* arr)
{
    RandArr(arr);

    int sum = 0;
    float middle,count = 0;

    for (size_t index = 0; index < array_size(arr); index++)
    {
        sum += array_get(arr, index);
        count++;
    }

    middle = sum / count;


    for (size_t index = 0; index < array_size(arr); index++)
    {
        if (array_get(arr, index) < middle)
        {
            cout << array_get(arr, index) << " ";
        }
    }
    cout << endl;
}

int main()
{
    Array* arr = NULL;
    size_t size;

    cin >> size;

    arr = array_create(size);
    task1(arr);
    array_delete(arr);
    arr = NULL;
    cin >> size;

    arr = array_create(size);
    task2(arr);
    array_delete(arr);
}