#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array *array_create_and_read(istream &input)
{
    long long n = 0;
    if (!(input >> n) || n < 0)
        return nullptr;
    Array *arr = array_create((size_t)n);
    for (size_t i = 0 ; i < (size_t)n ; ++i)
    {
        Data x;
        if (!(input >> x))
        {
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, x);
    }
    return arr;
}

// Задание 1
// Определить порядковый номер самого быстрого автомобиля.
// Если таких автомобилей несколько, то должны
// быть найдены номера первого и последнего из них.
void task1(const Array *arr)
{
    size_t size = array_size(arr);
    if (size == 0)
    {
        cout << "Array is empty\n";
        return;
    }

    Data max = array_get(arr, 0);
    size_t first = 0;
    size_t last = 0;
    for (size_t i = 1 ; i < size ; ++i)
    {
        Data speed = array_get(arr, i);
        if (speed > max)
        {
            max = speed;
            first = i;
            last = i;
        }
        else if (speed == max)
        {
            last = i;
        }
    }

    if (first == last)
        cout << first + 1 << "\n";
    else
        cout << first + 1 << " " << last + 1 << "\n";
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input file>\n";
        return 1;
    }
    ifstream input(argv[1]);
    if (!input)
    {
        cerr << "Cannot open file " << argv[1] << "\n";
        return 1;
    }

    Array *arr = array_create_and_read(input);
    if (arr == nullptr)
    {
        cerr << "Invalid input data\n";
        return 1;
    }
    task1(arr);
    array_delete(arr);
    return 0;
}
