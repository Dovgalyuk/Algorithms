#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "array.h"

typedef Array<int> MyArray;

template<typename Data>
void PrintArray(Array<Data>& toPrint)
{
    size_t arraySize = toPrint.size();
    for (int i = 0; i < arraySize; i++)
        std::cout << toPrint[i] << " ";
}

void Exec()
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
    int min = arr[0], max = arr[0];
    for (int i = 0; i < n; i++)
    {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
    }
    std::cout << "Minimal element: " << min << ' ' << "Maximum element: " << max << std::endl;
}

int main()
{
    MyArray *arr = new MyArray(10);

    if (arr->size() != 10)
        std::cout << "Invalid array size\n";

    PrintArray(*arr);

    for (int i = 0 ; i < 10 ; ++i)
        arr->set(i, i * 2);

    for (int i = 0 ; i < 10 ; ++i)
        if (arr->get(i) != i * 2)
            std::cout << "Invalid array element " << i << "\n";
    
    PrintArray(*arr);

    delete arr;

    Exec();
}
