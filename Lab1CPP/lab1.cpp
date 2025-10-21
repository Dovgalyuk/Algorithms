#include <iostream>
#include <fstream>
#include "array.h"

Array *read_array_from_file(std::istream& in)
{
    size_t size;
    in >> size;

    Array *arr = array_create(size);
    
    for (size_t i = 0; i < size; i++)
    {
        Data value;
        in >> value;
        array_set(arr, i, value);
    }
    return arr;
}

Array* read_array_size(std::istream& in)
{
    size_t size;
    in >> size;
    return array_create(size);
}

bool check_prime(int number)
{
    if (number <= 1) return false;
    if (number == 2) return true;
    
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0)
            return false;
    }
    return true;
}

void task1(Array *arr) 
{
    size_t arr_size = array_size(arr);
    int current = 2;
    size_t count = 0;
    
    while (count < arr_size) {
        if (check_prime(current)) {
            array_set(arr, count, current);
            count++;
        }
        current++;
    }

    for (size_t i = 0; i < arr_size; i++) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
}


void task2(Array *arr)
{
    size_t arr_size = array_size(arr);
    
    if (arr_size < 5) {
        return;
    }

    int sum = 0;
    for (size_t i = 0; i < 5; i++) {
        sum += array_get(arr, i);
    }
    
    int max_sum = sum;
    size_t start_index = 0;

    for (size_t i = 1; i <= arr_size - 5; i++) {
        sum = sum - array_get(arr, i - 1) + array_get(arr, i + 4);
        
        if (sum > max_sum) {
            max_sum = sum;
            start_index = i;
        }
    }

    for (size_t i = start_index; i < start_index + 5; i++) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    std::ifstream file(argv[1]);

    Array* array1 = read_array_size(file);
    task1(array1);
    array_delete(array1);

    Array* array2 = read_array_from_file(file);
    task2(array2);
    array_delete(array2);
    
    file.close();
    return 0;
}

