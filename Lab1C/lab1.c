#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "array.h"

// swap elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// swap array elements
void array_swap(Array* arr, const int i1, const int i2) {
    Data tmp = array_get(arr, i1);
    array_set(arr, i1, array_get(arr, i2)); 
    array_set(arr, i2, tmp);                
}

// quick sort
void Hoara_sort(Array* arr, const int first, const int last) {
    if (first >= last) return;
    int lastPtr = last, firstPtr = first;
    int pivot = array_get(arr, first + (last - first) / 2);
    while (firstPtr <= lastPtr) {
        while(array_get(arr, lastPtr) > pivot) lastPtr--;
        while(array_get(arr, firstPtr) < pivot) firstPtr++;
        if  (firstPtr <= lastPtr) {
            array_swap(arr, firstPtr, lastPtr);
            firstPtr++; 
            lastPtr--;
        }
    }
    Hoara_sort(arr, first, lastPtr);
    Hoara_sort(arr, firstPtr, last);
}

// print array 
void printArray(Array* arr) {
    for(size_t i = 0; i < array_size(arr); i++) {
        printf("%d ", array_get(arr, i));
    }
    printf("\n");
}

// checking for simple number
bool is_simple_number(const Data n) {
    for (int d = 2; d <= (int)sqrt(n)+1; d++)
            if (n % d == 0) {
                return false;
        }
    return true;
}

// read size and elements and create array
Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    // Create array 
    Array *arr = array_create(n, NULL);
    // Read array data 
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

// task 1 (completion simple numbers) 
void task1(Array *arr)
{
    array_set(arr, 0, 2);
    for (int x = 3, i = 1; i < array_size(arr); x++) {
        if(is_simple_number(x)) {
            array_set(arr, i, x);
            i++;
        } 
    }
    printArray(arr);
}

// task 2 (minimum difference) 
void task2(Array *arr)
{
    if (array_size(arr) < 2) {
        printf("incorrect array!");
        return;
    }
    Hoara_sort(arr, 0, array_size(arr) - 1);
    int min_dif = -1;
    int prev_even = -1;
    for (int i = 0; i < array_size(arr); i++) {
        if(array_get(arr,i) % 2 == 0) {
            if (prev_even != -1) {
                int dif = array_get(arr,i) - prev_even;
                if(min_dif == -1 || dif < min_dif)
                    min_dif = dif;
            }
            prev_even = array_get(arr,i);
        }
    }
    (min_dif == -1) ? printf("incorrect array!") : printf("the minimum difference between two even elements: %d", min_dif); 
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen("input.txt", "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    // Create another array here 
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
    
    return 0;
}