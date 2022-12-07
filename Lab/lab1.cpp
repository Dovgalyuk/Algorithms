#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

void MinAvg(Array* arr) 
{
    int avg = 0;
    cout << "Array: \n";
    for (int i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand() % 50 + 1);
        cout << array_get(arr, i) << " ";
    }

    for (int i = 0; i < array_size(arr); i++)
    {
        avg += array_get(arr, i);
    }

    cout << "\n" << "Less than the average number: \n";
    
    for (int i = 0; i < array_size(arr); i++)
    {
        if (avg / array_size(arr) > array_get(arr, i))
            cout << array_get(arr, i) << " ";
    }
}
int main()
{
    srand(time(NULL));
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    cout << "\n";
    Array* arr = array_create(size);
    MinAvg(arr);
    array_delete(arr);
    return 0;
}