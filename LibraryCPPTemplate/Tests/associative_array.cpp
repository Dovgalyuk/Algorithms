#include <iostream>
#include <ctime>
#include "associative_array.h"
using namespace std;

int main() 
{
    RBAssociativeArray array(to_string(0), to_string(0));
    int count = 1000000;
    for (int i = 0; i < count; ++i)
    {
        string Str = to_string(i);
        array.Insert(Str, Str);
    }
    srand(time(0));
    for (int i = 0; i < count; ++i) 
    {
        string Str = to_string(i);
        auto* P = array.SearchTree(Str);
        if (!P || P->getKey() != Str)
        {
            cout << "Data storage error " << i << "\n\n";
            return 1;
        }
    }
    for (int i = 0; i < 5; ++i) 
    {
        int id = rand() % count;
        string Str = to_string(id);
        array.DeleteNode(Str);
        auto* P = array.SearchTree(Str);
        if (!P || P->getKey() != Str)
        {
            cout << "Data deletion was not successful\t id: " << id << "\n\n";
            return 1;
        }
    }
}
