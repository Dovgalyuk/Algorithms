/*
Реализовать контейнер - динамический массив array с неизменяемым размером (на любом из языков)
Проверить работу соответствующей тестовой программы
Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами.
Нечетные элементы массива уменьшить на m, а элементы с нечетными номерами увеличить на n. m и n ввести с клавиатуры.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами.
В массиве найти элементы, которые в нем встречаются только один раз, и вывести их на экран.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.h"

using namespace std;

void task1(Array *arr)
{
    size_t size;
    double n, m;
    cout << "Введите размер массива: ";
    cin >> size;
    /*int* arr_random = new int[size];*/
    arr = array_create(size);
    srand(time(NULL));
    cout << "Созданный массив: " << endl;
    //создание массива
    for (size_t i = 0; i < array_size(size); i++) {
        array_set(arr, i, rand());
        cout << array_get(arr, i) << " ";
    } cout << endl;
    cout << "Введите m: ";
    cin >> m;
    cout << "Введите n: ";
    cin >> n;
    //обработка массива
    for (size_t i = 0; i < array_size(size); i++) {
        if (array_get(arr, i) % 2 != 0) {
            array_get(arr, i) -= m;
        }
        if (i % 2 != 0) {
            array_get(arr, i) += n;
        }
    }
    //вывод обработанного массива
    cout << "Обработанный массив: " << endl;
    for (size_t i = 0; i < array_size(size); i++) {
        cout << array_get(arr, i) << " ";
    }
}

void task2(Array *arr)
{
    size_t size;
    cout << "Введите размер массива: ";
    cin >> size;
    arr = array_create(size_t size);
    /*int* arr_random = new int[size];*/

    //создание массива
    srand(time(NULL));
    cout << "Созданный массив: " << endl;
    for (size_t i = 0; i < array_size(size); i++) {
        /*arr_random[i] = rand();*/
        array_set(arr, i, rand());
        cout << array_get(arr, i) << " ";
    } cout << endl;

    //обработка массива
    bool flag;
    for (size_t i = 0; i < array_size(size); i++) {
        for (size_t j = 0; j < array_size(size); j++) {
            flag = false;
            if (i != j and (array_set(arr, i) == array_set(arr, j))) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << array_get(arr, i) << " ";
        }
    }
}

int main()
{
    Array *arr = NULL;

    task1(arr);
    array_delete(arr);

    task2(arr);
    array_delete(arr);
}
