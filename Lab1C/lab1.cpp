#include <stdio.h>
#include "array.h"
#include <iostream>

using namespace std;
void task1(Array *arr)
{
    float count = 0, sum = 0;
    for (size_t i = 0; i < array_size(arr);i++)
    {
        array_set(arr, i, rand() % 10);
        if (array_get(arr, i) != 0)
        {
            count++;
            sum += array_get(arr, i);
        }
    }
    float middle = sum / count;
    cout << middle << endl;
}

void task2(Array *arr)
{
    int a, b, current = 0;
    cin >> a;
    cin >> b;
    for (size_t i = 0; i < array_size(arr);i++)
    {
        array_set(arr, i, rand() % 10);
        if (array_get(arr, i) < a || array_get(arr, i) > b)
        {
            array_set(arr, current, array_get(arr, i));
            current++;
        }
    }
    for (; current < array_size(arr); current++)
    {
        array_set(arr, current, 0);
    }
    for (size_t i = 0;i < array_size(arr);i++)
    {
        cout << array_get(arr, i) << " ";
    }
}

int main()
{
    Array *arr = nullptr;
    int n;
    cin >> n;
    arr = array_create(n);
    task1(arr);
    array_delete(arr);
    cin >> n;
    arr = array_create(n);
    task2(arr);
    array_delete(arr);
}
