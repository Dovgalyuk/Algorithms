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

void task1(Array *arr) 
{
    size_t arr_size = array_size(arr);
    size_t max_lenght = 0;
    size_t current_lenght = 0;
    
    for (size_t i = 0; i < arr_size; i++) {
        int value = array_get(arr, i);
        
        if (value % 2 != 0) {
            current_lenght++;
            if (current_lenght > max_lenght) {
                max_lenght = current_lenght;
            }
        } else {
            current_lenght = 0;
        }
    }
    
    std::cout << max_lenght << std::endl;
}


void task2(Array *arr)
{
    size_t arr_size = array_size(arr);
    
    for (size_t i = 0; i < arr_size; i++) {
        int value = array_get(arr, i);
        bool no_delitel = true;
        
        for (size_t j = 0; j < arr_size; j++) {
            if (i != j) {
                int other = array_get(arr, j);
                
                if (other != 0) {
                    if (value % other == 0) {
                        no_delitel = false;
                    }
                }
            }
        }
        
        if (no_delitel) {
            std::cout << value << " ";
        }
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    std::ifstream file(argv[1]);

    Array* array1 = read_array_from_file(file);
    task1(array1);
    array_delete(array1);

    Array* array2 = read_array_from_file(file);
    task2(array2);
    array_delete(array2);
    
    file.close();
    return 0;
}

