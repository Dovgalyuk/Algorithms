#include <iostream>
#include <algorithm>
#include "array.h"

typedef Array<int> MyArray;

int main()
{
    srand(4541);
    int n = -1;
    while (n <= 0)
    {
        std::cout << "Enter size of your array: ";
        std::cin >> n;
        std::cout << std::endl;
    }
    MyArray arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = rand();
    int smallest = arr[0], secondSmall = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (smallest > arr[i]) smallest = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= smallest && secondSmall > arr[i]) secondSmall = arr[i];
    }
    std::cout << "Smallest element: " << smallest << ' ' << "Second smallest element: " << secondSmall << std::endl;
}