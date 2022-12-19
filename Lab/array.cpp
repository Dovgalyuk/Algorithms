#include <iostream>
#include <ctime>
#include "array.h"

void getTheMostPopularNubmersInArray(Array* arr){

    size_t size = array_size(arr);

    
     Array* temp = array_create(size);
     for (size_t i = 0; i < array_size(temp); ++i) {
         array_set(temp, i, 0);
     }


    for (int i = 0; i < size; ++i)
    {

        bool found = false;
        for (int j = 0; j < i; ++j)
            if (array_get(arr,j) == array_get(arr, i))
            {
                found = true;
                array_set(temp, j, array_get(temp, j) + 1);     
                break;
            }
        if (!found)  array_set(temp, i, array_get(temp, i) + 1);     
    }



    int max = 0;
    for (int i = 0; i < size; ++i)
        if (max < array_get(temp, i))
        {
            max = array_get(temp, i);
        }


    std::cout << "The most popular number(s) - ";
    for (size_t i = 0; i < array_size(temp); i++)
    {
        if (array_get(temp, i) == max) {
            std::cout << array_get(arr, i)<<" ";
        }
    }

    array_delete(temp);
}

int main() {
    srand(time(0));
    size_t size;

    std::cout << "Enter size of array: ";
    std::cin >> size;

    Array* arr = array_create(size);


    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = rand() % 11;
        array_set(arr, i, value);
    }

    for (std::size_t i = 0; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
    }
    
        std::cout << std::endl;
    getTheMostPopularNubmersInArray(arr);
    array_delete(arr);
    return 0;
}