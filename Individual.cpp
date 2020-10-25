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
        arr[i] = rand();
    int min = INT_MAX, max = INT_MIN, minIndex = 0, maxIndex = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            minIndex = i;
        }
        if (arr[i] > max)
        {
            max = arr[i];
            maxIndex = i;
        }
    }
    int sum = 0;
    for (int i = minIndex + 1; i < maxIndex; i++)
    {
        sum += arr[i];
    }
    cout << "The summ is: " << sum;
}