#include <iostream>
#include <ctime>
#include "associative_array.h"
using namespace std;
int main() {
    RBAssociativeArray<string, string> array(to_string(NULL), to_string(NULL));
    int count = 800000;
    for (int i = 0; i < count; ++i) 
    {
        array.Insert(to_string(i), to_string(i));
    }
    srand(time(0));
    for (int i = 0; i < count; ++i) 
    {
        if (array.SearchTree(to_string(i)) == false)
        {
            cout << "Data storage error" << i << "\n\n";
            return 1;
        }
    }
    for (int i = 0; i < 5; ++i) 
    {
        int id = rand() % count;
        array.DeleteNode(to_string(id));

        if (array.SearchTree(to_string(id))==true)
        {
            cout << "Data deletion was not successful\t id: " << id << "\n\n";
            return 1;
        }
    }
}
