#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

int size_for_array()
{
    cout << "Input size for array";
    int size;
    cin >> size;
    return size;
}

int randNumber()
{
    return rand() % 1000 + 1;
}

void full(Array* array)
{
    srand(time(0));
    for (int i = 0; i < array_size(array); i++)
    {
        array_set(array, i, randNumber());
    }
}

void print(Array* array)
{
    for (int i = 0; i < array_size(array); i++)
    {
        cout << "(" << i << ")" << "=" << array_get(array, i) << endl;
    }
    cout << endl;
    cout << endl;
}

void search(Array* array, int max, int min)
{
    int check = 0;

    for (int i = 0; i < array_size(array); i++)
    {
        if ((array_get(array, i) >= min) && (array_get(array, i) < max))
        {
            cout << "(" << i << ")" << "=" << array_get(array, i) << endl;
            check++;
        }
    }

    if (check == 0)
    {
        if (min==10)
        {
            cout << "There are no two-digit numbers" << endl;
        }
        else
        {
            cout << "There are no three-digit numbers" << endl;
        }
    }
}

int main()
{
    int a = size_for_array();
    Array* array = array_create(a);
    full(array);
    print(array);
    search(array,100,10);
    search(array,1000,100);

    array_delete(array);
    return 0;
}
