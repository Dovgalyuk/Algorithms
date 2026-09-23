// Задание 2:
// Прочитать целое число N из файла, создать массив размерности N
// и заполнить его числами из файла. Определить, какое число в массиве
// встречается чаще всего. На входе числа от 0 до 1000.
// Программа должна работать за время O(N).
// Вывести результат на экран или в файл.

#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

const int kMaxValue = 1000;

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

void task2(Array *arr)
{
    int size = array_size(arr);

    int counts[kMaxValue + 1] = {0};
    for (int i = 0; i < size; ++i)
    {
        int value = array_get(arr, i);
        ++counts[value];
    }

    int best_value = 0;
    int best_count = counts[0];
    for (int v = 1; v <= kMaxValue; ++v)
    {
        if (counts[v] > best_count)
        {
            best_count = counts[v];
            best_value = v;
        }
    }

    cout << "Самое частое число: " << best_value << ", встречается " << best_count << " раз." << endl;
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    ifstream input(argv[1]);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    return 0;
}
