#include "tools.h"
#include <iostream>
#include <fstream>

using namespace std;

int find_max_odds_seq(Array *arr)
{
    int current = 0;
    int mx = 0;

    size_t size = array_size(arr);

    for (size_t i = 0; i < size; i++)
    {
        if (array_get(arr, i) % 2 != 0)
        {
            current++;

            if (current > mx)
                mx = current;
        }
        else
        {
            current = 0;
        }
    }

    return mx;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;
    ifstream input(argv[1]);

    Array *arr = array_create_and_read(input);

    if (arr == nullptr)
        return 1;

    cout << find_max_odds_seq(arr) << endl;

    array_delete(arr);

    return 0;
}