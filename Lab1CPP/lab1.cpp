#include <stdio.h>
#include "array.h"
#include <iostream>

using namespace std;

Array *array_create_and_read(FILE *input)
{
    int n;
    if (fscanf(input, "%d", &n) != 1){};
    /* Create array */
    Array *arr = array_create(n);
    /* Read array data */
    for (int i = 0 ; i < n ; ++i)
    {
        int x;
        if (fscanf(input, "%d", &x) != 1){};
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{   
    double num, size;
    float cnt_pos = 0, cnt_neg = 0, sum_pos = 0, sum_neg = 0;
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
    cout << (cnt_pos == 0 ? 0 : sum_pos / cnt_pos) << " "
     << (cnt_neg == 0 ? 0 : sum_neg / cnt_neg) << " ";
}

void task2(Array *arr)
{
    bool flag = false;
    int size = array_size(arr);
    for (int i = 0; i < size; i++) {
        int num1 = array_get(arr, i);
        bool temp = false;
        for (int j = 0; j < size; j++) {
            if (i == j){
                continue;}
            int num2 = array_get(arr, j);
            if (num2 == 0){
                continue;}
            if (num1 % num2 == 0) {
                temp = true;
                break;
            }
        }
        if (!temp) {
            if (flag) {
                cout << " ";
            }
            cout << num1;
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
