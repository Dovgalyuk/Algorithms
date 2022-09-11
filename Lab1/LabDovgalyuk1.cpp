#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

int arrayFillandSerch(arr *arr, int const size)
{
    bool check;
    int count = 0;

    int min = 999; 
    int max = 0; 
    int averege;

    arr *buf = array_create(size);

    array_set(buf, 0, min, max, averege);

    for (int i = 0; i < size;)
    {
        check = false;
        int randvalue = rand() % 101;

        for (int j = 0; j < i; j++)
        {
            if (array_get(arr, j) == randvalue)
            {
                check = true;
            }
        }
        if (!check)
        {
            array_set(arr, i, randvalue);
            if (randvalue > max)
            {
                max = randvalue;
            }
            if (randvalue < min)
            {
                min = randvalue;
            }
            cout << array_get(arr, i) << " // ";
            i++;
        }
    }
    average = max / min;
    for (int i = 0; i < size; i++)
    {
        if (array_get(arr, i) > averege)
        {
            count++;
            array_set(buf, i, count);
        }
    }
    cout << "\n\t Count value > average min and max : " << count<<"\n"<< "Position of numbers : ";
    for (int i = 0; i <= count; i++)
    {
        cout << array_get(buf, i)<<" ";
    }
    array_delete(buf);
    return count;
}

int main()
{
    srand(time(NULL));

    int value;
    cout << "Enter size of array : ";
    cin >> value;
    cout << "\n";

    arr *arr = array_create(value);
    arrayFillandSerch(arr, value);

    array_delete(arr);
    getline();

}
