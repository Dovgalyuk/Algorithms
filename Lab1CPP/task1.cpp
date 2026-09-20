#include <iostream>
#include <fstream>
#include <cmath>
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

void task1(Array *arr)
{
    size_t n = array_size(arr);
    if (n == 0) {
        cout << "Array is empty" << endl;
        return;
    }

    long long sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += array_get(arr, i);

    double average = static_cast<double>(sum) / static_cast<double>(n);

    size_t bestIndex = 0;
    double bestDiff = std::abs(array_get(arr, 0) - average);

    for (size_t i = 1; i < n; ++i)
    {
        double diff = std::abs(array_get(arr, i) - average);
        if (diff < bestDiff)
        {
            bestDiff = diff;
            bestIndex = i;
        }
    }

    cout << "Average: " << average << endl;
    cout << "Closest element: " << array_get(arr, bestIndex)
         << " (index " << bestIndex << ")" << endl;
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
    task1(arr);
    array_delete(arr);

    input.close();
    return 0;
}