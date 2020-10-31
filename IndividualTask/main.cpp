#include <iostream>
#include "array.h"

typedef Array<int> MyArray;
using namespace std;

int main()
{
    srand(4541);
    MyArray nums(size);
    int size;
    cin >> size;
    for (int i = 0; i < size; i++)
    {
        nums[i] = rand();
    }
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += nums[i];
    }
    cout << "Summa: " << sum;
}