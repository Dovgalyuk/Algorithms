#include <stdio.h>
#include "array.h"

Array *array_create_and_read(FILE *input)
{
    int n;
    fscanf(input, "%d", &n);
    /* Create array */
    Array *arr = array_create(n, NULL);
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
    size_t n = array_size(arr);
    int count = 0;
    for(size_t  i = 0 ; i < n; i++){
        int value = (int)array_get(arr,i);
        if(value % 2 == 0 || value % 3 == 0 || value % 5 ==0|| value % 7 == 0)
        count ++;
    }
    printf("%d\n", count);
}

void task2(Array *arr)
{
    size_t n = array_size(arr);
    int first = 1;  // флаг для первого найденного элемента
    
    for(size_t i = 0; i < n; i++){
        int current = (int)array_get(arr, i); 
        int indivisible = 1; 
        
        for(size_t j = 0; j < n; j++){
            if(i != j) { // не сравниваем с смим собой
                int other = (int)array_get(arr, j);//другой элемент
                if (other != 0 && current % other == 0)  {  
                    indivisible = 0;
                    break;
                }
            }
        }
        
        if(indivisible == 1) {
            if(!first) printf(" ");
            printf("%d", current);
            first = 0;
        }
    }
    printf("\n");
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
