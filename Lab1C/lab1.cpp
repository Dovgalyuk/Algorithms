#include <iostream>
#include <ctime>
#include "array.h"
#include "math.h"

using namespace std;

struct Array
{
    size_t size;
    Data* data;
};

void task1(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
    {
        if (!(rand() % 3))                       //According to statistics for 30 years, Veliky Novgorod has an average of 11 rainy days in August during which 93 mm of precipitation falls
            array_set(arr, i, rand() % 14 + 2);
        else
            array_set(arr, i, 0);
    }

    size_t rainyDays = 0;
    size_t precipitation = 0;
    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++)
    {
        cout << array_get(arr, i) << ' ';
        if (array_get(arr, i))
        {
            rainyDays++;
            precipitation += array_get(arr, i);
        }
    }
    cout << "\nNumber of rainy days: " << rainyDays << "\nAmount of precipitation per month: " << precipitation << "\nAverage precipitation: " << (float)precipitation / rainyDays << endl;
}

void task2(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
        array_set(arr, i, rand() % 202 - 101);

    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++)
        cout << array_get(arr, i) << ' ';

    Array *tempArr = array_create(array_size(arr));
    size_t evenElemCounter = 0;
    for (size_t i = 0; i < array_size(arr); i++)
        if (arr->data[i] % 2 == 0)
            array_set(tempArr, evenElemCounter++, array_get(arr, i));
    
    if (evenElemCounter < 2)
    {
        cout << endl << "Not enough even elements.";
        return;
    }

    int minDifference = tempArr->data[0] - tempArr->data[1];
    int curDifference;
    for (size_t i = 0; i < evenElemCounter - 1; i++)
    {
        for (size_t j = i + 1; j < evenElemCounter; j++)
        {
            curDifference = -abs(array_get(tempArr, i) - array_get(tempArr, j));
            if (minDifference > curDifference)
                minDifference = curDifference;
        }
    }
    array_delete(tempArr);

    cout << endl << "Minimum difference of even elements: " << minDifference;
}

int main()
{
    srand((int)time(NULL));

    Array *arr = NULL;
    size_t size;

    /* Create array here */
    cout << "Enter array size: ";
    cin >> size;
    arr = array_create(size);
    
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    cout << "\nEnter array size: ";
    cin >> size;
    arr = array_create(size);
    
    task2(arr);
    array_delete(arr);
}