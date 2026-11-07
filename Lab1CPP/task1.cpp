#include <fstream>
#include <iostream>
#include "array.h"

using namespace std;

Array* read_array(const char* filename)
{
    ifstream input(filename);

    size_t size;
    input >> size;

    Array* arr = array_create(size);

    for (size_t i = 0; i < size; ++i)
    {
        Data value;
        input >> value;
        array_set(arr, i, value);
    }

    return arr;
}

int main(int argc, char** argv)
{
    if (argc < 2)
        return 1;

    Array* arr = read_array(argv[1]);

    const int days_in_month[] =
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    size_t day = 0;

    for (int month = 0; month < 12; ++month)
    {
        int sum = 0;

        for (int i = 0; i < days_in_month[month]; ++i)
        {
            if (day >= array_size(arr))
                break;

            sum += array_get(arr, day);
            ++day;
        }

        if (month > 0)
            cout << " ";

        cout << sum;
    }

    cout << endl;

    array_delete(arr);

    return 0;
}