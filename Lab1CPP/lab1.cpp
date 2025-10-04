#include <iostream>
#include <fstream>
#include <unordered_map>
#include "array.h" 
using namespace std;
void save_even_indices(Array* arr)
{
    size_t n = array_size(arr);
    size_t even_count = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (array_get(arr, i) % 2 == 0)
            ++even_count;
    }

    Array* indices = array_create(even_count);
    size_t j = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (array_get(arr, i) % 2 == 0)
        {
            array_set(indices, j, static_cast<Data>(i));
            ++j;
        }
    }

    for (size_t i = 0; i < even_count; ++i)
    {
        cout << array_get(indices, i) << " ";
    }
    cout << "\n";

    array_delete(indices);
}

void find_elements_appearing_twice(Array* arr)
{
    size_t n = array_size(arr);
    unordered_map<Data, int> freq;
    for (size_t i = 0; i < n; ++i)
    {
        ++freq[array_get(arr, i)];
    }

    for (const auto& p : freq)
    {
        if (p.second == 2)
        {
            cout << p.first << " ";
        }
    }
    cout << "\n";
}

Array* array_create_and_read(istream& input)
{
    size_t n;
    input >> n;

    Array* arr = array_create(n);
    for (size_t i = 0; i < n; ++i)
    {
        Data val;
        input >> val;
        array_set(arr, i, val);
    }
    return arr;
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    ifstream input(argv[1]);
    if (!input)
        return 1;

    Array* arr1 = array_create_and_read(input);
    if (!arr1) return 1;
    save_even_indices(arr1);
    find_elements_appearing_twice(arr1);
    array_delete(arr1);

    Array* arr2 = array_create_and_read(input);
    if (!arr2) return 1;
    save_even_indices(arr2);
    find_elements_appearing_twice(arr2);
    array_delete(arr2);

    return 0;
}