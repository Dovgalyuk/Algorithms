#include <iostream>
#include "associative_array.h"
using namespace std;

int main()
{
    AssociativeArray array("0", "0");
    int count = 1000000;
    for (int i = 1; i < count; ++i)
    {
        string Str = to_string(i);
        array.add(Str, Str);
    }
    for (int i = 0; i < count; ++i)
    {
        string Str = to_string(i);
        auto P = array.search(Str);
        if (P->key != Str)
        {
            cout << "Data storage error ";
            return 1;
        }
    }
    for (int i = 0; i < count; ++i)
    {
        string Str = to_string(i);
        array.remove(Str);
        if (array.search(Str) != nullptr)
        {
            cout << "Error deleting an element";
            return 1;
        }
    }
}
