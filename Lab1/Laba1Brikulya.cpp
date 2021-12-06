#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

int GiveMeSize() {
    int size;
    bool check;
    do {
        cout << "Give me size of the massive: ";
        cin >> size;
        if (cin.fail())
        {
            check = false;
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "\nOh-oh, looks like you made a mistake. Here is your next chanse\n";
        }
        else {
            check = true;
        }
    } while (check == false);
    cout << "\n";
    return size;
}

void FillingArray(Array* array) 
{
    srand(time(nullptr));
    cout << "We got this:\n";
    for (int i = 0; i < array_size(array); i++) {
        array_set(array, i, rand() % 41 - 20);
        cout << i + 1 << " element: " << array_get(array, i) << "\n";
    }
    cout << "\n";
}

int main()
{
    int size = GiveMeSize();
    Array* array = array_create(size);
    FillingArray(array);
    int min = 1000, max = -1000, mink = 0, maxk = 0;
    for (int i = 0; i < size; i++)
    {
        if (array_get(array, i) < min)
        {
            min = array_get(array, i);
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (array_get(array, i) > max)
        {
            max = array_get(array, i);
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (array_get(array, i) == min)
        {
            mink++;
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (array_get(array, i) == max)
        {
            maxk++;
        }
    }
    cout << "kolvo max = " << maxk << "\n" << "kolvo min = " << mink << "\n";

    array_delete(array);
    return 0;
}