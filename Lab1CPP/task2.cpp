#include <iostream>
#include <fstream>
#include "array.h"
// Прочитать целое число из файла, создать массив такой размерности и заполнить его числами из файла. 
// Найти минимальную разность между разными чётными элементами массива. Вывести результат на экран или в файл.

Array *array_create_and_read(std::ifstream &input)
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
    bool found = false;
    int min_diff = 0;

    size_t n = array_size(arr);
    for (size_t i = 0; i < n; i++)
    {
        int a = array_get(arr, i);
        if (a % 2 != 0)
        {
            continue;
        }

        for (size_t j = i + 1; j < n; j++)
        {
            int b = array_get(arr, j);
            if (b % 2 != 0)
            {
                continue;
            }

            int diff = a - b;
            if (a < b)
            {
                diff = b - a;
            }
            if (!found || diff < min_diff)
            {
                found = true;
                min_diff = diff;
            }
        }
    }

    if (found)
    {
        std::cout << "Min difference: " << min_diff << "\n";
    }
    else
    {
        std::cout << "No even elements" << "\n";
    }
}

int main(int argc, char **argv)
{
    (void)argc;
    std::ifstream input(argv[1]);

    Array *arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    return 0;
}