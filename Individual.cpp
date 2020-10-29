#include <iostream>
#include <algorithm>
#include <climits>
#include "array.h"

typedef Array<int> MyArray;
using namespace std;

int main()
{
    srand(4541);
    size_t n;
    cin >> n;
    MyArray arr(n);
    for (int i = 0; i < n; i++)
        arr.set(i, rand());
    int min = INT_MAX, max = INT_MIN, minNumIndex = 0, maxNumIndex = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr.get(i) < min)
        {
            min = arr.get(i);
            minNumIndex = i;
        }
        if (arr.get(i) > max)
        {
            max = arr.get(i);
            maxNumIndex = i;
        }
    }
    int sum = 0, start, end;
    if (minNumIndex <= maxNumIndex)
    {
        start = minNumIndex + 1;
        end = maxNumIndex;
    } else
    {
        start = maxNumIndex + 1;
        end = minNumIndex;
    }
    for (int i = start; i < end; i++)
    {
        sum += arr.get(i);
    }
    cout << "The summ is: " << sum;
}