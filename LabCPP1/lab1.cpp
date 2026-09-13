#include "lab1.h"

Array *array_create_and_read(ifstream& input, bool num)
{
    int n;
    if (!(input >> n) || n <= 0) {
        return nullptr;
    }
    Array* arr = array_create(n);

    if (num)
    {
        for (int i = 0; i < n; i++)
        {
            int value = i + 1;
            array_set(arr, i, value);
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            int x;
            input >> x;
            array_set(arr, i, x);
        }
    }

    return arr;
}

void array_print(ostream& out, Array* arr)
{
    size_t size = array_size(arr);
    for (size_t i = 0; i < size; i++) {
        if (i > 0)
        {
            out << " ";
        }
        out << array_get(arr, i);
    }
    out << endl;
}
