#include "array.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void task1()
{
    size_t size;
    double n, m;
    cout << "Enter the size of the array: ";
    cin >> size;
    /*int* arr_random = new int[size];*/
    Array* arr = array_create(size);
    srand(time(NULL));
    /*cout << "Созданный массив: " << endl;*/
    //создание массива
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand());
        /*cout << array_get(arr, i) << " ";*/
    }
    cout << "Enter m and n: ";
    cin >> m >> n;
    //обработка массива
    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) % 2 != 0) {
            array_set(arr, i, array_get(arr, i) - m);
        }
        if (i % 2 != 0) {
            array_set(arr, i, array_get(arr, i) + n);
        }
    }
    //вывод обработанного массива
    cout << "Array: " << endl;
    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }
    array_delete(arr);
}

void task2()
{
    size_t size;
    cout << endl << "Enter the size of the array: ";
    cin >> size;
    Array* arr = array_create(size);
    //создание массива
    srand(time(NULL));
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand());
    }

    //обработка массива
    bool flag = true;
    for (size_t i = 0; i < array_size(arr); i++) {
        for (size_t j = 0; j < array_size(arr); j++) {
            flag = false;
            if (i != j and (array_get(arr, i) == array_get(arr, j))) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << array_get(arr, i) << " ";
        }
    }
    array_delete(arr);
}

int main()
{
    /*Array* arr = NULL;*/
    task1();
    /*array_delete(arr);*/

    task2();
    /*array_delete(arr);*/
}