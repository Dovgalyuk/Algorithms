#include <iostream>
#include "array.h"

using namespace std;

void ArrRandFill(Array *arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
        array_set(arr, i, rand() % 101);
}

bool ArrHalfCheck(Array *arr)
{
    size_t i, sum1, sum2 = 0;
    for (i; i <= array_size(arr) / 2; i++)
        sum1 += array_get(arr, i);
    for (i; i < array_size(arr); i++)
        sum2 += array_get(arr, i);
    if (sum1 > sum2)
        return 1;
    else
        return 0;
}

int ArrDecCheck(Array *arr)
{
    size_t i, j, sumG, sumT, res = 0;
    for (i; i <= array_size(arr) / 3; i++)
    {
        sumT = 0;
        for (j; j < 10 * i && j < array_size(arr); j++)
            sumT += array_get(arr, j);
        if (sumT > sumG)
        {
            sumG = sumT;
            res = i;
        }
    }
    return res;
}

int main()
{
    int input;
    cin >> input;
    Array *arr = array_create(input);
    ArrRandFill(arr);
    if (ArrHalfCheck(arr) == true)
        cout << "1" << endl;
    else
        cout << "2" << endl;
    cout << ArrDecCheck(arr);
}