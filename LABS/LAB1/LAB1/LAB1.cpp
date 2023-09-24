#include <stdio.h>
#include "array.h"
#include<iostream>

using namespace std;

void task1(Array* arr)
{
    int count_negative = 0 , count_positiove = 0;

    for (int i = 0; i < array_size(arr); i++)
    {
        if (array_get(arr, i) > 0)
            count_positiove++;

        else if (array_get(arr, i) == 0)
            continue;

        else
            count_negative++;
    }

    Array* p_arr = array_create(count_positiove);
    Array* n_arr = array_create(count_negative);

    for (int z = 0, i = 0, j = 0; i < array_size(arr); z++)
    {
        if (array_get(arr, i) > 0)
        {
            array_set(p_arr, i , array_get(arr, z));
            i++;

        }

        else if (array_get(arr, i) == 0)
            continue;

        else
        {
            array_set(n_arr, j, array_get(arr, z));
            j++;
        }
    }

    array_delete(p_arr); 
    array_delete(n_arr);
}

void task2(Array* arr)
{
    int counter = 1;
    size_t id;
    for (size_t i = 0, j = 0; i < array_size(arr); j++)
    {

        if (j == array_size(arr))
        {
            j = 0;
            i++;
            if (counter == 2)
            {
                cout << array_get(arr, i) << endl;
                cout << array_get(arr, i) << endl;
            }
        }

        if (array_get(arr, i) == array_get(arr, j) && i!=j)
        {
            counter++;
        }

    }
}

void fill_array(Array *arr)
{
    for (int i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
    }
}


int main()
{
    Array* arr = NULL;
    /* Create array here */

    arr = array_create(10);

    if (array_size(arr) != 10)
    {
        cout << "Invalid array size\n";
        array_delete(arr);
        return 1;
    }

    for (int i = 0; i < 10; ++i)
        array_set(arr, i, i * 2);

    for (int i = 0; i < 10; ++i)
    {
        if (array_get(arr, i) != i * 2)
        {
            cout << "Invalid array element " << i << "\n";
            array_delete(arr);
            return 1;
        }
    }

    array_delete(arr);

    srand(NULL);
    size_t size;

    setlocale(LC_ALL, "ru");
    cout << "Введите размер массива для task1" << endl;
    cin >> size;

    arr = array_create(size);
    fill_array(arr);

    task1(arr);
    array_delete(arr);


    /* Create another array here */
    cout << "Введите размер массива для task2" << endl;
    cin >> size;

    arr = array_create(size);
    fill_array(arr);

    task2(arr);
    array_delete(arr);
}
