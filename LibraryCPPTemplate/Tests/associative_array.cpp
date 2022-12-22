#include <iostream>
#include <ctime>
#include "associative_array.h"
using namespace std;

int main()
{
    AssociativeArray array(to_string(0), to_string(0));
    int count = 1000000;
    for (int i = 0; i < count; ++i)
    {
        string Str = to_string(i);
        array.add(Str, Str);
    }
    for (int i = 0; i < count; ++i)
    {
        string Str = to_string(i);
        auto P = array.search(Str);
        if (P != Str)
        {
            cout << "Data storage error ";
            return 1;
        }
    } 
}
