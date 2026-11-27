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
    double sum = 0;
    for (size_t i = 0;i < array_size(arr);++i){
        sum += array_get(arr,i);
    }
    double average  = sum / array_size(arr);
    std::cout << "Avg =" << average << "\n";
    std::cout << "Элементы меньше среднего:";
    for (size_t i = 0; i < array_size(arr);++i){
        if(array_get(arr,i)< average)
            std::cout << array_get(arr,i) <<" ";
    }
    std::cout << "\n";
}

int main(int argc, char **argv)
{
    (void)argc;
    std::ifstream input(argv[1]);

    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    return 0;
}