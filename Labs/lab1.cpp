#include "array.h"
#include <iostream>

using namespace std;

/*void printArray(Array *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << array_get(arr, i) << " ";
    }
    cout << endl;
}*/

void task1(Array *arr, int m, int n)
{
    size_t size = array_size(arr);

    //cout << "Изначальный  для  1:" << endl;
    //printArray(arr, size);

    for (size_t i = 0; i < size; i++)
{
    int value = array_get(arr, i);
    if ((value % 2 != 0) && (i % 2 != 0))
    {
        // Если число нечетное и имеет нечетный индекс
        array_set(arr, i, value - m );
        array_set(arr, i, value + n);
    }
    else if (i % 2 != 0)
    {
        // Если только индекс нечетный
        array_set(arr, i, value + n);
    }
    else if (value % 2 != 0)
    {
        // Если только число нечетное
        array_set(arr, i, value - m);
    }
}



    //cout << "после  задания 1:" << endl;
   //printArray(arr, size);
}

void task2(Array *arr)
{
    size_t size = array_size(arr);

    //cout << "Изначальный  2:" << endl;
    //printArray(arr, size);

    for (size_t i = 0; i < size; i++)
    {
        int current = array_get(arr, i);
        bool isDivisible = false;

        for (size_t j = 0; j < size; j++)
        {
            if (i != j)
            {
                int other = array_get(arr, j);
                if (other != 0 && current % other == 0)
                {
                    isDivisible = true;
                    break;
                }
            }
        }

        if (!isDivisible)
        {
            cout << current << " ";
        }
    }

    cout << endl;
}

void CreateArray(Array *arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
        array_set(arr, i, rand() % 101); // числа от 0 до 100
}

int main()
{
    Array *arr = NULL;
    size_t size;
    int m, n;

    cout << "размер: ";
    cin >> size;

    cout << "m: ";
    cin >> m;

    cout << "n: ";
    cin >> n;

    arr = array_create(size);
    CreateArray(arr, size);

    task1(arr, m, n);
    array_delete(arr);

    cout << " размер нового масс: ";
    cin >> size;

    arr = array_create(size);
    CreateArray(arr, size);

    task2(arr);
    array_delete(arr);

    return 0;
}
