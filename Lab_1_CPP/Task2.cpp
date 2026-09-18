#include <fstream>
#include <iostream>
#include "array.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    }
    ifstream input(argv[1]);
    if (!input)
    {
        return 1;
    }
    int n;
    if (!(input >> n) || n < 0)
    {
        return 1;
    }
    Array *arr = array_create(static_cast<size_t>(n));
    if (arr == nullptr)
    {
        return 1;
    }
    int frequency[1001] = {};
    for (int i = 0; i < n; ++i)
    {
        int value;
        if (!(input >> value) || value < 0 || value > 1000)
        {
            array_delete(arr);
            return 1;
        }
        array_set(arr, static_cast<size_t>(i), value);
        ++frequency[value];
    }
    cout << "Элементы встречающиеся один раз: ";
    bool first = true;
    for (int i = 0; i < n; ++i)
    {
        int value = array_get(arr, static_cast<size_t>(i));
        if (frequency[value] == 1)
        {
            if (!first)
            {
                cout << ' ';
            }
            cout << value;
            first = false;
        }
    }
    if (first)
    {
        cout << "нет";
    }
    cout << '\n';
    array_delete(arr);
    return 0;
}
