#include <iostream>
#include <fstream>
#include "array.h"
//найти элементы, которые в массиве встречаются ровно два раза. Программа должна работать за время O(N)
using namespace std;

Array* read_array_from_file(const char* filename)
{
    ifstream input(filename);

    size_t size;
    input >> size;

    Array* arr = array_create(size);

    for (size_t i = 0; i < size; i++)
    {
        Data value;
        input >> value;
        array_set(arr, i, value);
    }

    return arr;
}

int main(int argc, char* argv[]) {
    if (argc < 2) { return 1; }

    Array* arr = read_array_from_file(argv[1]);
    size_t size = array_size(arr);

    int counters[1001] = {0};

    for (size_t i = 0; i < size; i++)
    {
        int value = array_get(arr, i);
        if (value >= 0 && value <= 1000)
        {
            counters[value]++;
        }
    }
    //O(n)
    for (int i = 0; i < 1001; i++)
    {
        if (counters[i] == 2)
        {
            cout << i << " ";
        }
    }

    array_delete(arr);
    return 0;
}