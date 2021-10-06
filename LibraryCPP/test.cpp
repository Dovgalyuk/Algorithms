//
// Created by Nechaev on 05.10.2021.
//
#include <iostream>
#include <ctime>
#include "array.cpp"

void fillingTheArray(Array* arr){
    for (int i = 0; i <  array_size(arr); i++)
    {
        array_set(arr, i, rand() % 1000 - 100);
    }
}

void arrayOutput(Array* arr){
    for (int i = 0; i < array_size(arr); i++)
    {
        std::cout << array_get(arr, i) << " ";
    }
}

void searchForTwoMaxima(int &min1, int &min2, Array* arr){
    if (array_size(arr) > 1)
    {
        min1 = array_get(arr, 0);
        min2 = array_get(arr, 1);

        if (min2 < min1)
        {
            min1 = array_get(arr, 1);
            min2 = array_get(arr, 0);
        }
        for (int i = 2; i < array_size(arr); i++)
        {
            if (array_get(arr, i) < min1)
            {
                min2 = min1;
                min1 = array_get(arr, i);
            }
            else if (array_get(arr, i) < min2)
                min2 = array_get(arr, i);

        }

        arrayOutput(arr);

        std::cout << std::endl << "min1 = " << min1 << " min2 = " << min2;
    }
    else
    {
        std::cout << array_get(arr, 0);
    }
}

int main() {
    srand(time (0));
    int min1 = INT_MAX, min2 = INT_MAX;
    Array* arr = array_create(10);

    fillingTheArray(arr);



    array_delete(arr);
}
