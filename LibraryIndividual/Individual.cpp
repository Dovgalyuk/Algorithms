#include <iostream>
#include <algorithm>
#include <climits>
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
    int smallest = INT_MAX, secondSmall = arr[0]; // didn't understand why this variables can't have value of the same element
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < smallest)
        {
            secondSmall = smallest;
            smallest = arr[i];
        }
        else if (arr[i] < secondSmall)
            secondSmall = arr[i];
    }
    std::cout << "Smallest element: " << smallest << ' ' << "Second smallest element: " << secondSmall << std::endl;
}