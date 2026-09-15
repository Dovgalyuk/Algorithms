#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::ifstream &input)
{
    int n;
    input >> n;
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        array_set(arr, i, i+2);
    }
    return arr;
}

void task1(Array *arr, std::ofstream &output)
{ 
    size_t size = array_size(arr);
    if (size == 0) { return; }

    for (size_t i = 0; i < size; i++)
    {
        int val = array_get(arr, i);
        if (val < 2) continue;

        for (size_t j = val * val - 2; j < size; j += val)
        {
            array_set(arr, (int)j, 0);
        }
    }
        
    size_t writePos = 2; 
    for (size_t i = 2; i < size; i++) 
    {
        if (array_get(arr, i) != 0) 
        {
            if (i != writePos) 
            {
                int temp = array_get(arr, i);      
                array_set(arr, i, 0);              
                array_set(arr, writePos, temp);
            }
            writePos++;
        }
    }

    for (size_t i = 0; i < size; i++)
    {
        output << array_get(arr, i) << " ";
        std::cout << array_get(arr, i) << " ";
    }
    output << std::endl;
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    Array *arr = NULL;

    std::ifstream input (argv[1]);
    std::ofstream output (argv[2]);
    arr = array_create_and_read(input);
    task1(arr, output);
    array_delete(arr);

    input.close();
    output.close();
}
