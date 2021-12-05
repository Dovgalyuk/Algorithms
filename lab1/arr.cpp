#include <iostream>
#include "array.h"
#include <ctime>


void fill(Array<int>& a)
{
    srand(time(nullptr));
    for (int i = 0; i < a.size(); ++i)
    {
        a.set(i, rand() % 10);
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

int find(Array<int>& array)
{
    double avg = 0.0;
    for (int i = 0; i < array.size(); ++i)
    {
        avg += array[i];
    }
    avg /= array.size();
    std::cout << "average: " << avg << std::endl;

    double t = 1.0;
    int min = array.get(0);
    for (int i = 0; i < array.size(); ++i)
    {
        if (abs(array[i] - avg) < t)
        {
            t = abs(array[i] - avg);
            min = array[i];
        }

    }
    return min;
}

int main()
{
    int size;
    std::cin >> size;
    Array<int> array = Array<int>(size);

    fill(array);
    std::cout << "answer: " << find(array) << std::endl;

    return 0;
}
