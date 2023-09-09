#include "array.h"
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    size_t size = array_size(arr);
    size_t kolvo = 0;
    for (size_t i = 0; i < size; i++) {
        //достаточно проверять кратность для 2,3,5,7 для эффективности алгоритма
        if (array_get(arr, i) % 2 == 0 || array_get(arr, i) % 3 == 0 || array_get(arr, i) % 5 == 0 || array_get(arr, i) % 7 == 0)
            kolvo++;
    }
    cout << kolvo << endl;
}

void task2(Array *arr)
{
    size_t currentID = 0;
    size_t maxSum = 0;

    if (array_size(arr) <= 5) {
        for (size_t i = 0; i < array_size(arr); ++i)
            cout << array_get(arr, i) << endl;
    }
    else
    {
        for (size_t i = 0; i < array_size(arr) - 4; ++i) {
            size_t currentSum = array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2) + array_get(arr, i + 3) + array_get(arr, i + 4);
            if (currentSum > maxSum) {
                maxSum = currentSum;
                currentID = i;
            }
        }

        for (size_t i = currentID; i < currentID + 5; ++i)
            cout << array_get(arr, i) << endl;
    }
}

void CreateArray(Array* arr) {
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand());
}

int main()
{
    srand((unsigned int)time(NULL)); //random
    Array *arr = NULL;
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