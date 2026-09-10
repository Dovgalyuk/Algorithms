#include <iostream>
#include <fstream>
#include "array.h"

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

void task1(Array *arr)
{
    int size = array_size(arr);
    double sum1 = 0, sum2 = 0, sum3 = 0;
    int count1 = 0, count2 = 0, count3 = 0;

    for (int i = 0; i < size && i < 10; ++i)
    {
        sum1 += array_get(arr, i);
        count1++;
    }
    for (int i = 10; i < size && i < 20; ++i)
    {
        sum2 += array_get(arr, i);
        count2++;
    }
    for (int i = 20; i < size && i < 30; ++i)
    {
        sum3 += array_get(arr, i);
        count3++;
    }

    std::cout << "Среднее в первой декаде: " << (count1 ? sum1 / count1 : 0) << std::endl;
    std::cout << "Среднее во второй декаде: " << (count2 ? sum2 / count2 : 0) << std::endl;
    std::cout << "Среднее в третьей декаде: " << (count3 ? sum3 / count3 : 0) << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: Task1 <input_file>" << std::endl;
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open file" << std::endl;
        return 1;
    }
    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    return 0;
}