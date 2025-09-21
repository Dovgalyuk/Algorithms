#include <iostream>
#include <fstream>
#include "array.h"

Array *array_create_and_read(std::ifstream& input)
{
    int n;
    input >> n;
    Array *arr = array_create(n);
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    size_t n = array_size(arr);
    for(size_t i = 0 ; i < n / 2; i++){
        Data t1 = array_get(arr, i);
        Data t2 = array_get(arr, n - i - 1);
        array_set(arr, i, t2);
        array_set(arr, n-i-1, t1);
    } 
}

void task2(Array *arr)
{
    if(array_size(arr) < 5){
        return;
    }
    int sum1 = 0;
    size_t i1 = 0;
    for(size_t i = 0; i < 5;i++){
        sum1 += array_get(arr, i);
    }
    int sum2 = sum1;
    for(size_t i = 1; i < array_size(arr) - 5; i++){
        sum2 = sum2 - array_get(arr,i-1) + array_get(arr,i+4);
        if(sum2 > sum1){
            sum1 = sum2;
            i1 = i;
        }
    }
    for(size_t i = 0; i < 5; i++){
        std::cout << array_get(arr, i1 + i) << " ";
    }
}

void displayArr(Array *arr) { 
    for(size_t i = 0; i < array_size(arr);i++){
        std::cout << array_get(arr,i) << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    Array *arr = nullptr;
    std::ifstream input(argv[1]);
    if(!input.is_open()) return 1;
    arr = array_create_and_read(input);
    displayArr(arr);
    task1(arr);
    displayArr(arr);
    array_delete(arr);
    Array *arr1 = nullptr;
    arr1 = array_create_and_read(input);
    task2(arr1);
    array_delete(arr1);
    input.close();
}
