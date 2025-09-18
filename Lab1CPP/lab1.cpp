#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    
    Array *arr = array_create(n);
  
    for(int i = 0; i < n; i++)
    { 
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{ 
    if(array_size(arr) == 0)
    {
        return;
    }

    double sum = 0;
    for(size_t i = 0; i < array_size(arr); i++)
    { 
        sum += array_get(arr, i);
    }

    double arithmetic_mean;
    arithmetic_mean = sum / array_size(arr);
    
    for(size_t i = 0; i < array_size(arr); i++)
    { 
        if(array_get(arr, i) < arithmetic_mean)
        {
            std::cout << array_get(arr, i) << " ";
        }
    }
    std::cout << ". ";
}

void task2(Array *arr)
{
    for(size_t i = 0; i < array_size(arr); i++)
    {
        bool isOne = true;

        for(size_t j = 0; j < array_size(arr); j++)
        {
            if(array_get(arr, i) == array_get(arr, j) && i != j)
            {
                isOne = false;
                break;
            }
        }

        if(isOne)
        {
            std::cout<<array_get(arr, i)<<" ";
        }
    }
}

int main(int argc, char **argv)
{ 
    Array *arr = NULL;
    std::ifstream input(argv[1]);
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
}