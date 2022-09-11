#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

int arrayFillandSerch(Array *arr, int const size)
{
    int count = 0;

    int min = 999; 
    int max = 0; 
    int averege;

    Array *buf = array_create(size);
    for (int i = 0; i < size; i++)
    {

        int randvalue = rand() % 101+1;

        if (randvalue > max)
        {
            max = randvalue;
        }
        if (randvalue < min)
        {
            min = randvalue;
        }
        array_set(arr, i, randvalue);
        cout << array_get(arr, i) << " // ";
    }
    averege = (max+min)/2;
    cout<<"\nPosition of numbers : ";
    for (int i = 0; i < size; i++)
    {
        if (array_get(arr, i) > averege)
        {
            count++;
            array_set(buf, count, i);
            cout << i << " ";
        }
        
    }
    cout << "\nCount value > averege min and max : " << count<<"\n";
    return count;
}

int main()
{
    srand(time(NULL));

    int value;
    cout << "Enter size of array : ";
    cin >> value;
    cout << "\n";

    Array *arr = array_create(value);
    arrayFillandSerch(arr, value);

    array_delete(arr);
    system("pause");

}
