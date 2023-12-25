#include <stdio.h>
#include "array.h"
#include <iostream>
#include <ctime>

using namespace std;

void task1(Array *arr)
{
    setlocale(LC_ALL, "Rus");
    size_t size;
    cout << "¬ведите размер массива: ";
    cin >> size;
    arr = array_create(size);

    for (size_t i = 0; i < size; i++)
    {
        int num = rand() % 50;
        array_set(arr, i, num);
        cout << "Ёлемент " << i << ":" << num << endl;
    }

    Data sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        Data num = array_get(arr, i);
        if (num <= Data(20))
        {
            sum += num;
        }
    }
    cout << "—умма элементов, не привышающих 20 =  " << sum << endl;
    array_delete(arr);
}

void task2(Array *arr)
{
    size_t size;
    cout << "¬ведите размер массива: ";
    cin >> size;
    arr = array_create(size);
    for (size_t i = 0; i < size; i++)
    {
        int num = rand() % 50;
        array_set(arr, i, num);
        cout << "Ёлемент " << i << ":" << num << endl;
    }
    Data min = array_get(arr, 0);
    Data max = array_get(arr, 0);

    size_t minIndex = 0;
    size_t maxIndex = 0;

    for (size_t i = 1; i < size; i++)
    {
        Data num = array_get(arr, i);
        if (num < min)
        {
            min = num;
            minIndex = i;
        }
        if (num > max)
        {
            max = num;
            maxIndex = i;
        }
    }
    int sum = 0;
    size_t start = minIndex < maxIndex ? minIndex : maxIndex;
    size_t end = minIndex < maxIndex ? maxIndex : minIndex;

    for (size_t i = start + 1; i < end; i++)
    {
        sum += array_get(arr, i);
    }
    cout << "—умма между макс и мин = " << sum << endl;
    array_delete(arr);

}

int main()
{
    Array *arr = NULL;
    /* Create array here */
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    task2(arr);
    array_delete(arr);
}
