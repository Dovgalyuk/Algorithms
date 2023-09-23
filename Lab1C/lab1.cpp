#include <iostream>
#include "array.h"

using namespace std;

void RandArr(Array* arr)
{
    for (size_t index = 0; index < array_size(arr); index++)
    {
        array_set(arr, index, rand() % 100);
    }
}

void task1(Array* arr)
{
    RandArr(arr);

    int count = 0;
    float middle = 0,
        minArrMember = FLT_MAX,
        maxArrMember = -FLT_MAX;

    for (size_t index = 0; index < array_size(arr); index++)
    {
        if (array_get(arr, index) < minArrMember)
            minArrMember = array_get(arr, index);

        if (array_get(arr, index) > maxArrMember)
            maxArrMember = array_get(arr, index);
    }

    middle = static_cast<float>((maxArrMember + minArrMember) / 2);

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

    float middle = 0,
        count = 0,
        sum = 0;

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
    Array* arr = nullptr;
    size_t size = 0;

    cin >> size;

    arr = array_create(size);
    task1(arr);
    array_delete(arr);
    arr = nullptr;
    cin >> size;

    arr = array_create(size);
    task2(arr);
    array_delete(arr);
}