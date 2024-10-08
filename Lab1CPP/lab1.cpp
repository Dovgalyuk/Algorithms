#include <iostream>
#include <stdexcept>
#include "array.h"
#include "lab1.h"

InputData array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) < 1) {
        throw std::invalid_argument("Wrong size");
    }
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) < 1) throw std::invalid_argument("Wrong num");
        array_set(arr, i, x);
    }

    int a = 0,b = 0;
    if (fscanf(input, "%d", &a) < 1) throw std::invalid_argument("Wrong num a");
    if (fscanf(input, "%d", &b) < 1) throw std::invalid_argument("Wrong num b");
    
    return InputData{arr, a, b};
}

int task1(InputData inputArrAB)
{
    int summ = 0;
    int size = array_size(inputArrAB.array);
    for (int i = 0; i < size; i++) {
        int num = array_get(inputArrAB.array, i);
        if (num % inputArrAB.a == 0 || num % inputArrAB.b == 0) {
            summ += num;
        }
    }

    return summ;
}

int task2(Array *arr)
{
    int minMinus = __INT_MAX__;
    int size = array_size(arr);

    for(int i = 1; i < size; i++) {
        for(int j = i; j > 0 && array_get(arr, j - 1) > array_get(arr, j); j--) {
            int temp = array_get(arr, j - 1);
            array_set(arr, j - 1, array_get(arr, j));
            array_set(arr, j, temp);
        }
    }

    int evenNum = -1;
    for (int i = 0; i < size; i++) {
        int current = array_get(arr, i);
        if (current % 2 == 0) {
            if (evenNum != -1) {
                int diff = current - evenNum;
                if (diff < minMinus) {
                    minMinus = diff;
                }
            }
            evenNum = current;
        }
    }

    return minMinus;
}
