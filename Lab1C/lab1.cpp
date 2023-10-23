#include "array.h"
#include <time.h>
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    size_t size = array_size(arr);
    int start = 2;
    int end = 5;
    for (size_t i = 0; i < size; i++)
    {
        array_set(arr, i, rand() % (end - start + 1) + start);
    }

    int kolvo_5 = 0;
    int kolvo_4 = 0;
    int kolvo_3 = 0;
    int kolvo_2 = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (array_get(arr, i) == 5)
        {
            kolvo_5++;
        }
        else if (array_get(arr, i) == 4)
        {
            kolvo_4++;
        }
        else if (array_get(arr, i) == 3)
        {
            kolvo_3++;
        }
        else if (array_get(arr, i) == 2)
        {
            kolvo_2++;
        }
    }
    cout << "Piterok: " << kolvo_5 << "; Shetverok: " << kolvo_4 << "; Troek: " << kolvo_3 << "; Dvoek: " << kolvo_2 << endl;
}

size_t findSmallestPosition(Array *arr, size_t startPosition)
{
    size_t smallestPosition = startPosition;

    for (size_t i = startPosition; i < array_size(arr); i++)
    {
        if (array_get(arr, i) < array_get(arr, smallestPosition))
            smallestPosition = i;
    }
    return smallestPosition;
}
void selectionSort(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
    {
        size_t smallestPosition = findSmallestPosition(arr, i);
        int a = array_get(arr, i);
        int b = array_get(arr, smallestPosition);
        array_set(arr, i, b);
        array_set(arr, smallestPosition, a);
    }
}
void task2(Array *arr)
{
    size_t size = array_size(arr);
    selectionSort(arr);

    Array *nambers = NULL;
    nambers = array_create(size);

    int count = 0;
    int minDiff = 1000000;
    for (size_t i = 0; i != size; i++)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            array_set(nambers, count, array_get(arr, i));
            count += 1;
        }
    }
    for (int i = 1; i < count; i++)
    {
        if (count > 1)
        {
            minDiff = min(minDiff, array_get(nambers, i) - array_get(nambers, i - 1));
        }
    }
    if (count < 2)
    {
        cout << "Nexvataet shisel!" << endl;
        return;
    }
    cout << "Minimalnaia raznitsa = " << minDiff << endl;
    array_delete(nambers);
}

void CreateArray(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
        array_set(arr, i, rand());
}

int main()
{
    srand((unsigned int)time(NULL));
    Array *arr = NULL;
    size_t size;

    cin >> size;
    arr = array_create(size);
    task1(arr);
    array_delete(arr);

    cin >> size;
    arr = array_create(size);
    CreateArray(arr);
    task2(arr);
    array_delete(arr);
}