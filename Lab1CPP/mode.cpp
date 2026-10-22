#include "tools.h"
#include <iostream>
#include <fstream>

using namespace std;

int find_mode(Array *arr)
{
    int counts[1001] = {};

    size_t size = array_size(arr);

    for (size_t i = 0; i < size; i++)
    {
        int value = array_get(arr, i);
        counts[value]++;
    }

    int mode = 0;

    for (int i = 1; i <= 1000; i++)
    {
        if (counts[i] >= counts[mode])
            mode = i;
    }

    return mode;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    ifstream input(argv[1]);

    if (!input)
        return 1;

    Array *arr = array_create_and_read(input);

    if (arr == nullptr)
        return 1;

    cout << find_mode(arr) << endl;

    array_delete(arr);
}