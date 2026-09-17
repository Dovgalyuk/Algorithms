
#include <fstream>
#include <iostream>
#include "../LibraryCPP/array.h"

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
    long long sum = 0;
    for (int i = 0; i < n; ++i)
    {
        int value;
        if (!(input >> value))
        {
            array_delete(arr);
            return 1;
        }
        array_set(arr, static_cast<size_t>(i), value);
        sum += value;
    }
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        if (array_get(arr, static_cast<size_t>(i)) > sum)
        {
            ++count;
        }
    }
    cout << "Количество элементов больше суммы: " << count << '\n';
    cout << "Номера элементов: ";
    bool first = true;
    for (int i = 0; i < n; ++i)
    {
        if (array_get(arr, static_cast<size_t>(i)) > sum)
        {
            if (!first)
            {
                cout << ' ';
            }
            cout << i + 1;
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
