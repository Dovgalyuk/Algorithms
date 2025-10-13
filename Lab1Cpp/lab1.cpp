#include <iostream>
#include <fstream>
#include <iomanip>
#include "array.h"

Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    Array *arr = array_create(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    size_t size = array_size(arr);
    int pos_sum = 0;
    int pos_count = 0;
    int neg_sum = 0;
    int neg_count = 0;
    
    for (size_t i = 0; i < size; i++)
    {
        int val = array_get(arr, i);
        if (val > 0)
        {
            pos_sum = pos_sum + val;
            pos_count = pos_count + 1;
        }
        else if (val < 0)
        {
            neg_sum = neg_sum + val;
            neg_count = neg_count + 1;
        }
    }
    
    if (pos_count > 0)
    {
        double pos_avg = (double)pos_sum / pos_count;
        std::cout << std::fixed << std::setprecision(2) << pos_avg << std::endl;
    }
    else
    {
        std::cout << "0.00" << std::endl;
    }
    
    if (neg_count > 0)
    {
        double neg_avg = (double)neg_sum / neg_count;
        std::cout << std::fixed << std::setprecision(2) << neg_avg << std::endl;
    }
    else
    {
        std::cout << "0.00" << std::endl;
    }
}

void task2(Array *arr)
{
    size_t size = array_size(arr);
    int max_sum = 0;
    size_t best_start = 0;
    bool first = true;
    
    for (size_t i = 0; i <= size - 5; i++)
    {
        int sum = 0;
        for (size_t j = i; j < i + 5; j++)
        {
            sum = sum + array_get(arr, j);
        }
        
        if (first || sum > max_sum)
        {
            max_sum = sum;
            best_start = i;
            first = false;
        }
    }
    
    for (size_t i = best_start; i < best_start + 5; i++)
    {
        std::cout << array_get(arr, i);
        if (i < best_start + 4)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

int main(int, char **argv)
{
    std::ifstream input(argv[1]);
    
    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    
    input.close();
    return 0;
}