#include "array.h"
#include "math.h"

#include <iostream>
#include <ctime>


using namespace std;

void task1(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
    {
            array_set(arr, i, rand());
    }

    int count = 0;

    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++)
    {
        cout << array_get(arr, i);
        if (i != array_size(arr)-1) cout << ' ';
        int num = array_get(arr, i);
        for (; num!=0; num/=10) {
            count += num%10;
        }
    }
    cout << "\nSum of all digits of all array numbers - " << count << endl;
}

void task2(struct Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
        array_set(arr, i, rand() % 202 - 101);

    cout << "Array: ";
    for (size_t i = 0; i < array_size(arr); i++)
        cout << array_get(arr, i) << ' ';

    Array *tempArr = array_create(array_size(arr));
    size_t evenElemCounter = 0;
    for (size_t i = 0; i < array_size(arr); i++){
        if (array_get(arr, i) % 2 == 0) array_set(tempArr, evenElemCounter++, array_get(arr, i));
    }
    if (evenElemCounter < 2)
    {
        cout << endl << "Not enough even elements.";
        return;
    }

    int minDifference = abs(array_get(tempArr, 0) - array_get(tempArr, 1));
    int curDifference;
    for (size_t i = 0; i < evenElemCounter - 1; i++)
    {
        for (size_t j = i + 1; j < evenElemCounter; j++)
        {
            curDifference = abs(array_get(tempArr, i) - array_get(tempArr, j));
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

    struct Array *arr = NULL;
    size_t size;

    /* Create array here */
    cout << "Enter array size - ";
    cin >> size;
    arr = array_create(size);
    
    task1(arr);
    array_delete(arr);

    /* Create another array here */
    cout << "\nEnter array size - ";
    cin >> size;
    arr = array_create(size);
    
    task2(arr);
    array_delete(arr);
}