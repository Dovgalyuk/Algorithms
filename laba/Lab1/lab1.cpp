#include <iostream>
#include <ctime>
#include "array.cpp"

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

void searchA(Array* array)//Search for two-digit numbers
{
    int check = 0;
    cout << "search two-digit numbers" << endl;
    for (int i = 0; i < array_size(array); i++)
    {
        if ((array_get(array, i)>=10)&&(array_get(array, i) < 100))
        {
            cout << "(" << i << ")" << "=" << array_get(array, i) << endl;
            check++;
        }
    }
    if (check == 0)
    {
        cout << "There are no two-digit numbers" << endl;
    }
}
void searchB(Array* array)//Search for three-digit numbers
{
    int check = 0;
    cout << "search three-digit numbers" << endl;
    for (int i = 0; i < array_size(array); i++)
    {
        if ((array_get(array, i) >= 100) && (array_get(array, i) < 1000))
        {
            cout << "(" << i << ")" << "=" << array_get(array, i) << endl;
            check++;
        }
    }
    if (check == 0)
    {
        cout << "There are no three-digit numbers" << endl;
    }
}


int main()
{
    int a = size_for_array();
    Array* array = array_create(a);
    full(array);
    print(array);
    searchA(array);
    searchB(array);
    array_delete(array);
    return 0;
}
