#include "Lab1CPP.h"

Array* array_create_and_read(ifstream& input)
{
    int n;
    if (!(input >> n) || n <= 0) {
        return nullptr;
    }
    Array* arr = array_create(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
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