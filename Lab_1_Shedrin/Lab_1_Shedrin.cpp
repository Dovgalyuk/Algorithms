#include <iostream>
#include "../LibraryCPP/array.h"
#include<math.h>
using namespace std;

int Randims(int range_max,int range_min) {
     return ((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
}

int main()
{
    int leng = 0;
    cin >> leng;
    Array *arr = array_create(leng);

    for (size_t i = 0; i < leng; i++)
    {
        array_set(arr, i, Randims(100,-100));
    }
    for (size_t i = 0; i < leng; i++)
    {
       cout << "[" << array_get(arr, i) << "] ";
    }
    int max = array_get(arr, 0);
    for (size_t i = 0; i < leng; i++)
    {
        if (max < array_get(arr, i)) max = array_get(arr, i);
    }
    cout << "\n max = " << max;
    int element = 0;
    for (size_t i = 0; i < leng; i++)
    {
        if (abs(array_get(arr, i))>max) element++;
    }
    cout << "\n elemets > abs count : " << element;
    return 0;
}

