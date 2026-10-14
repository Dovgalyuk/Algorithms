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

// Задание 2
// Сжать последовательность с помощью
// алгоритма RLE. Вывести результат на экран.
void task2(const Array *arr)
{
    size_t size = array_size(arr);
    size_t i = 0;
    while (i < size)
    {
        Data value = array_get(arr, i);
        size_t count = 1;
        while (i + count < size && array_get(arr, i + count) == value)
            ++count;
        if (i > 0)
            cout << " ";
        cout << value << "x" << count;
        i += count;
    }
    cout << "\n";
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
    task2(arr);
    array_delete(arr);
    return 0;
}
