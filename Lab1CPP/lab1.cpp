#include "lab1.h"
#include <cstdio>
#include <stdio.h>
Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) < 0)
    {
        return nullptr;
    }
    Array *arr = new Array(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) < 0)
        {
            delete arr;
            return nullptr;
        }
        arr->set(i, x);
    }
    return arr;
}

std::vector<Data> task1(Array *arr)
// найти в массиве элементы, меньшие чем среднее арифметическое среди всех чисел массива
{
    std::vector<Data> ans;
    Data sum = 0;
    for (size_t i = 0; i < arr->size(); i++)
    {
        sum += arr->get(i);
    }

    double average = double(sum) / double(arr->size());
    for (size_t i = 0; i < arr->size(); i++)
    {
        if (double(arr->get(i)) < average)
        {
            ans.push_back(arr->get(i));
        }
    }
    return ans;
}
std::vector<Data> task2(Array *arr)
// найти в массиве элементы, которые не делятся ни на какие другие элементы этого массива
{
    std::vector<Data> ans;
    for (size_t i = 0; i < arr->size(); i++)
    {
        auto current = arr->get(i);
        auto passing = true;
        for (size_t j = 0; j < arr->size(); j++)
        {
            auto subEl = arr->get(j);
            if(subEl!=0&&current%subEl==0){
                passing = false;
            }
        }
        if(passing){
            ans.push_back(current);
        }
    }
    return ans;
}
