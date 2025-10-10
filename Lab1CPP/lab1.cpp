#include <stdio.h>
#include "array.h"
#include <iostream>

using namespace std;

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        fscanf(input, "%d", &x);
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{   
    double num, size, cnt_pos, cnt_neg, sum_pos, sum_neg;
    size = array_size(arr);
    for (int i = 0; i < size; i++){
        num = array_get(arr, i);
        if (num < 0){
            cnt_neg += 1;
            sum_neg += num;
        }
        if (num > 0){
            cnt_pos += 1;
            sum_pos += num;
        }
    }
    cout << sum_pos / cnt_pos << sum_neg / cnt_neg;
}

void task2(Array *arr)
{
    bool flag = false;
    int size, num1, num2;
    size = array_size(arr);
    for (int i = 0; i < size; i++){
        bool tmp = false;
        for (int j = 0; j < size; j++){
            num1 = array_get(arr,i);
            num2 = array_get(arr,j);
            if (num2 == 0){
                continue;
            }
            if (i == j){
                continue;
            }
            if (num1 % num2 == 0){
                tmp = true;
                break;
            }
        }
        if (!tmp){
            if (flag){
                cout << " ";
            }
            else{
                cout << num1;
            }
            flag = true;
        }
    }
}

int main(int argc, char **argv)
{
    Array *arr = NULL;
    FILE *input = fopen(argv[1], "r");
    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    fclose(input);
}
