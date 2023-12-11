/*
Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. Определить сколько из чисел массива кратны хотя бы одному из чисел в диапазоне от 2 до 9.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами. Определить, какое число в массиве встречается чаще всего.
*/
#include "array.h"

#include <ctime>
#include <iostream>

using namespace std;

void task1(Array *arr)
{
    size_t arr_len = array_size(arr);
    cout << "Array:";
    for (size_t i = 0; i < arr_len; i++) {
        array_set(arr, i, (rand()%100) );
        cout << " " << array_get(arr, i);
    }

    int cnt_multiple = 0;
    cout << "\n\nNumbers dividable without remainder:\n";
    for (size_t i = 0; i < arr_len; i++)
    {
        Data num = array_get(arr, i);
        if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0) {
            cout << num << " ";
            cnt_multiple++;
        }
    }
    cout << "\nThe number of multiple numbers of the array is: " << cnt_multiple << endl;
}

void task2(Array *arr)
{
    size_t arr_len = array_size(arr);
    cout << "Array:";
    for (size_t i = 0; i < arr_len; i++) {
        array_set(arr, i, (rand()%10) );
        cout << " " << array_get(arr, i);
    }

    int cnt_repeats_max = 0;
    size_t id_max = 0;
    for (size_t i = 0; i < arr_len - 1; i++)
    {   
        int cnt_repeats = 0;
        
        Data num = array_get(arr, i);
        for (size_t j = i + 1; j < arr_len; j++)
        {
            if(array_get(arr, j) == num) {
                cnt_repeats++;
            }
        }

        if (cnt_repeats_max < cnt_repeats) {
            cnt_repeats_max = cnt_repeats;
            id_max = i;
        }
    }

    if (cnt_repeats_max == 0 && arr_len > 1) {
        cout << "\n\nAll numbers of arrray is unique\n";
    } else {
        cout << "\n\nNumber " << array_get(arr, id_max) << " occurs more often then the others\n";
    }
}

int main()
{
    srand((int)time(0));
    Array *arr = NULL;
    cout << "Task 1\n\nenter array size\n>>> ";
    /* Create array here */
    size_t size_arr = 0;
    cin >> size_arr;
    arr = array_create(size_arr);

    task1(arr);
    array_delete(arr);

    cout << "-----------------------------------------------------\nTask 2\n\nenter array size\n>>> ";
    /* Create another array here */
    size_arr = 0;
    cin >> size_arr;
    arr = array_create(size_arr);

    task2(arr);
    array_delete(arr);
    return 0;
}
