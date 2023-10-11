#include"array.h"
#include<iostream>
#include<vector>
#include<ctime>


using namespace std;

void task1(Array* arr)
{
  /* int mas[12] = { 2,-4,-2,4,2,-1,0,0,1,1,-3,3 };
   for (int i = 0; i < array_size(arr); ++i) {
       array_set(arr, i, mas[i]);
   }*/

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

    for (size_t i = 0, p = 0, n=0; i < array_size(arr); i++)
    {
        if (array_get(arr, i) > 0)
        {
            array_set(p_arr, p, array_get(arr, i));
            p++;
        }

        else if (array_get(arr, i) == 0)
            continue;

        else
        {
            array_set(n_arr, n, array_get(arr, i));
            n++;
        }
    }

    array_delete(p_arr);
    array_delete(n_arr);
}

void task2(Array* arr)
{
  /*  int mas[12] = { 2,4,2,4,2,1,1,1,1,1,3,3 };
   for (int i = 0; i < array_size(arr); ++i) {
       array_set(arr, i, mas[i]);
   }*/

    vector<Data> arr_num(1);
    arr_num[0] = array_get(arr, 0);

    vector<Data> arr_count_num(1);
    arr_count_num[0] = 1;

    bool flag;

    for (size_t i = 1; i < array_size(arr); i++)
    {
        Data buff = array_get(arr, i);
        flag = 1;
  
        for (vector<int>::size_type j = 0; j < arr_num.size(); j++)
        {
            if (buff == arr_num[j])
            {
                flag = 0;
                arr_count_num[j]++;
                break;
            }
        }
        if (flag)
        {
            arr_num.push_back(buff);
            arr_count_num.push_back(1);
        }
    }

    cout << "\nѕовтор€ющие два раза числа(если они есть):" << endl;

    for (vector<int>::size_type i = 0; i < arr_count_num.size(); i++)
    {
        if (arr_count_num[i] == 2)
        {
            cout << " " << arr_num[i];
        }
    }
}

void fill_array(Array* arr)
{
    for (size_t i = 0; i < array_size(arr); i++)
    {
        array_set(arr, i, rand());
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    setlocale(LC_ALL, "ru");

    /* Create array here */

    Array* arr = NULL;
    size_t size;

    cout << "\n¬ведите размер массива дл€ task1" << endl;
    cin >> size;
    arr = array_create(size);
    fill_array(arr);
    task1(arr);
    array_delete(arr);


    /* Create another array here */
    cout << "\n¬ведите размер массива дл€ task2" << endl;
    cin >> size;
    arr = array_create(size);
    fill_array(arr);
    task2(arr);
    array_delete(arr);
}
