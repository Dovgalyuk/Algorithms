#include <iostream>
#include <fstream>
#include <vector>
#include "array.h"

using namespace std;

Array* array_create_and_read(istream& input)
{
    size_t n;
    input >> n;
    Array* arr = array_create(n);
    for (size_t i = 0; i < n; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    size_t n = array_size(arr);
    if (n == 0) {
        cout << "Array is empty" << endl;
        return;
    }

    Data min_val = array_get(arr, 0);
    Data max_val = array_get(arr, 0);

    for (size_t i = 1; i < n; ++i) {
        Data current = array_get(arr, i);
        if (current < min_val) min_val = current;
        if (current > max_val) max_val = current;
    }

    double average = (static_cast<double>(min_val) + max_val) / 2.0;
    vector<size_t> indices;

    for (size_t i = 0; i < n; ++i) {
        if (array_get(arr, i) > average) {
            indices.push_back(i);
        }
    }

    cout << "Array: ";
    for (size_t i = 0; i < n; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << "\nMin: " << min_val << ", Max: " << max_val;
    cout << "\nAverage of min and max: " << average;
    cout << "\nNumber of elements greater than average: " << indices.size();
    cout << "\nTheir indices: ";
    for (size_t idx : indices) {
        cout << idx << " ";
    }
    cout << "\n";
}

void task2(Array* arr)
{
    size_t n = array_size(arr);
    vector<Data> result;

    for (size_t i = 0; i < n; ++i) {
        Data current = array_get(arr, i);
        if (current == 0) continue;

        bool divisible = false;
        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                Data other = array_get(arr, j);
                if (other != 0 && current % other == 0) {
                    divisible = true;
                    break;
                }
            }
        }

        if (!divisible) {
            result.push_back(current);
        }
    }

    cout << "Array: ";
    for (size_t i = 0; i < n; ++i) {
        cout << array_get(arr, i) << " ";
    }
    cout << "\nElements not divisible by any other element: ";
    for (Data val : result) {
        cout << val << " ";
    }
    cout << "\n";
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    ifstream input(argv[1]);
    if (!input)
    {
        cerr << "Cannot open file: " << argv[1] << endl;
        return 1;
    }

    cout << "=== Task 1: Elements greater than average of min and max ===" << endl;
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    cout << "\n=== Task 2: Elements not divisible by any other element ===" << endl;
    arr = array_create_and_read(input);  
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}