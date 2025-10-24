#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array* array_create_and_read(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

//здесь я нахожу первый и последний максимум - 1 задача
void task1(Array* arr)
{
    int max = array_get(arr, 0);
    size_t first_num = 0, last_num = 0;
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        int a = array_get(arr, i);
        if (a > max)
        {
            max = a;
            first_num = last_num = i;
        }
        else if (a == max)
        {
            last_num = i;
        }
    }
    cout << "Task 1: Max = " << max << ", first index = " << first_num << ", last index = " << last_num << endl;
}

//здесь я нахожу число которое встречается чаще всего - 2 задача
void task2(Array* arr)
{
    size_t n = array_size(arr);
    int very_chasto = array_get(arr, 0);
    int max_num = 1;

    for (size_t i = 0; i < n; ++i) {
        int tecuhiy = array_get(arr, i);
        int num = 0;
        for (size_t j = 0; j < n; ++j)
        {
            if (array_get(arr, j) == tecuhiy) {
                num++;
            }
        }
        if (num > max_num) {
            max_num = num;
            very_chasto = tecuhiy;
        }
    }
    cout << "Task 2: Most frequent = " << very_chasto << " (occurs " << max_num << " times)" << endl;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    ifstream input(argv[1]);
    if (!input.is_open()) {
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
}