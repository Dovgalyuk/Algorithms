// Задание 1:
// Прочитать целое число N из файла, создать массив размерности N
// и заполнить его числами из файла. Найти средние арифметические
// положительных и отрицательных элементов массива.
// Вывести результат на экран или в файл.

#include <iostream>
#include <fstream>
#include <iomanip>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream &input)
{
    int n;
    input >> n;
    Array *arr = array_create(n);

    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array *arr)
{
    double positive_sum = 0;
    int positive_count = 0;
    double negative_sum = 0;
    int negative_count = 0;

    int size = array_size(arr);
    for (int i = 0; i < size; ++i)
    {
        int value = array_get(arr, i);
        if (value > 0)
        {
            positive_sum += value;
            ++positive_count;
        }
        else if (value < 0)
        {
            negative_sum += value;
            ++negative_count;
        }
    }

    cout << fixed << setprecision(2);

    if (positive_count == 0)
        cout << "Положительных элементов не было." << endl;
    else
        cout << "Среднее положительных элементов: " << positive_sum / positive_count << endl;

    if (negative_count == 0)
        cout << "Отрицательных элементов не было." << endl;
    else
        cout << "Среднее отрицательных элементов: " << negative_sum / negative_count << endl;
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    ifstream input(argv[1]);

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    return 0;
}
