#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array *array_create_and_read(FILE *input) {
    int n;
    if(fscanf(input, "%d", &n)!=1) {
        return NULL;
    };

    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    if (arr == NULL) { // проверка на успешное создание массива
        return NULL;
    }

    for (int i = 0 ; i < n ; ++i) {
        int x;
        if(fscanf(input, "%d", &x)!=1){
            array_delete(arr);
            return NULL;
        };
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr) {
    int max = 0;
    int firstMaxElement = 0;
    int lastMaxElement = 0;

    for (int i = 0 ; i < (int)array_size(arr) ; ++i) {
        if ((int)array_get(arr, i) > max) {
            max = (int)array_get(arr, i);
            firstMaxElement = i;
            lastMaxElement = i;
        } else if ((int)array_get(arr, i) == max) {
            lastMaxElement = i;
        }
    }
    printf("%d %d\n", firstMaxElement, lastMaxElement);
}

void task2(Array *arr) {
    int maxSum = 0;
    int size = (int)array_size(arr);
    for (int i = 0 ; i < size - 5 ; ++i) {
        int curSum = (int)(array_get(arr, i) + array_get(arr, i + 1) + array_get(arr, i + 2) + array_get(arr, i + 3) + array_get(arr, i + 4));
        if (curSum > maxSum) {
            maxSum = curSum;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    if (!input) {
        return 1;
    }
    arr = array_create_and_read(input);
    if (arr){
        task1(arr);
        array_delete(arr);
    } else {
        return 1;
    }
    /* Create another array here */
    arr = array_create_and_read(input);
    if (arr){
        task2(arr);
        array_delete(arr);
    } else {
        return 1;
    }
    
    fclose(input);
    return 0;
}