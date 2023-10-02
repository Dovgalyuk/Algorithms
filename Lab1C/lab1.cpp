#include "array.h"
#include<iostream>
#include<vector>
#include<ctime>



using namespace std;

void task1(Array* arr)
{
    int count_negative = 0, count_positiove = 0;

    for (size_t i = 0; i < array_size(arr); i++)
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

    for (size_t z = 0, i = 0, j = 0; i < array_size(arr); z++)
    {
        if (array_get(arr, i) > 0)
        {
            array_set(p_arr, i, array_get(arr, z));
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
    // у меня было два варианта сортировка изначального массива или дополнительная память. Выбрал второе.
    vector<Data> arr_num(1);
    arr_num[0] = array_get(arr, 0);

    vector<Data> arr_count_num(1);
    arr_count_num[0] = 1;

    for (size_t i = 1; i < array_size(arr); i++)
    {
        Data buff = array_get(arr, i);
        for (int j = 0; j < arr_num.size(); j++)
        {
            if (buff == arr_num[j])
            {
                arr_count_num[j]++;
                arr_num.push_back(buff);
                arr_count_num.push_back(1);
                break;
            }
        }

    }

    cout << "\n\n Повторяющие два раза числа(если они есть):" << endl;


    for (int i = 0; i < arr_count_num.size(); i++)
    {
        if (arr_count_num[i] == 2)
        {
            cout << " " << arr_num[i];
        }
    }
}

void fill_array(Array* arr)
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

    srand(NULL);
    size_t size;

    setlocale(LC_ALL, "ru");
    cout << "\nВведите размер массива для task1" << endl;
    cin >> size;

    arr = array_create(size);
    fill_array(arr);

    task1(arr);
    array_delete(arr);


    /* Create another array here */
    cout << "\nВведите размер массива для task2" << endl;
    cin >> size;

    arr = array_create(size);
    fill_array(arr);

    task2(arr);
    array_delete(arr);
}
