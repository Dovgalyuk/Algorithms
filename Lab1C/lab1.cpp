#include <iostream>
#include "array.h"
#include <cmath>
#include <ctime>
using namespace std;

void task1(Array *arr)
{
    size_t size = array_size(arr);
    double reverseR = 0; // 1/R
    size_t R = 0;        // R
    for (size_t i = 0; i < size; i++)
    {
        // 1/R = 1/r1 + 1/r2...
        double element = array_get(arr, i);
        element = pow(element, -1);
        reverseR += element;
    }
    R = 1 / reverseR;
    cout << "total resistance: " << R << endl;
}

void task2(Array *arr)
{
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; ++i)
    {
        bool isUnique = true;
        for (size_t j = 0; j < size; ++j)
        {
            if (i != j && array_get(arr, i) == array_get(arr, j))
            {
                isUnique = false;
                break;
            }
        }
        if (isUnique)
        {
            cout << array_get(arr, i) << " ";
        }
    }
}

void FillArray(Array *arr)
{
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
    {
        array_set(arr, i, rand() % 20);
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    Array *arr = NULL;
    size_t size;

    /* Create array here */
    cin >> size;
    arr = array_create(size);
    FillArray(arr);
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    cin >> size;
    arr = array_create(size);
    FillArray(arr);
    task2(arr);
    array_delete(arr);
}
