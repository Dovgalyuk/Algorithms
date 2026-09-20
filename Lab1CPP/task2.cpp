#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream &input)
{
    int n;
    input >> n;

    Array *arr = array_create(n);

    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task2(Array *arr)
{
    const int MAX_VALUE = 1000;
    static int counter[MAX_VALUE + 1];

    for (int i = 0; i <= MAX_VALUE; ++i)
        counter[i] = 0;

    size_t n = array_size(arr);
    for (size_t i = 0; i < n; ++i)
    {
        int v = array_get(arr, i);
        if (v >= 0 && v <= MAX_VALUE)
            counter[v]++;
    }

    int bestValue = 0;
    int bestCount = 0;
    for (int v = 0; v <= MAX_VALUE; ++v)
    {
        if (counter[v] > bestCount)
        {
            bestCount = counter[v];
            bestValue = v;
        }
    }

    cout << "Most frequent element: " << bestValue
         << " (occurs " << bestCount << " times)" << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input) {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    Array *arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}