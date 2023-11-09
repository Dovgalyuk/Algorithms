#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "array.h"

#define MAX_DAYS 365
#define MAX_RAINFALL 1870

void task1(Array *arr);

int main()
{
    Array *arr = NULL;
    /* Create array here */
    task1(arr);
    array_delete(arr);
}

void free_function(void *p) {
    free(p);
}

//void printArray(Array *arr, char *nameMonth[12], size_t daysMonth[12]) {
//    size_t m = 0, mD = 0;
//    printf("Array: \n");
//    while(m != 12 && mD != array_size(arr)){
//        printf("%s :\n", nameMonth[m]);
//        for (size_t i = 0 ; i < daysMonth[m] && mD != array_size(arr); i++)
//        {
//            printf("%d ", *(int*)array_get(arr, mD));
//            mD++;
//            if(mD == array_size(arr) || i + 1  == daysMonth[m]) {
//                printf("[%ld]\n", i+1);
//            }
//        }
//        m++;
//    }
//}

size_t rainfallYear(Array *arr, char *nameMonth[12], size_t daysMonth[12], int result[12]) {
    size_t m = 0, mD = 0;
    int sum;
    while(m != 12 && mD != array_size(arr)){
        sum = 0;
        for (size_t i = 0 ; i < daysMonth[m] && mD != array_size(arr); i++)
        {
            sum += *(int*)array_get(arr, mD);
            mD++;
        }
        result[m] = sum;
        m++;
    }
    return m;
}

void task1(Array *arr)
{
    size_t daysMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char *nameMonth[] = {"Jan", "Feb", "March", "April", "May", "June", "July", "August", "Sept", "Oct", "Nov", "Dec"};
    size_t size, m = 0;
    int rainfallMonth[12];
    if(!scanf("%zu", &size) || size > MAX_DAYS + 1 || size < 1) {
        printf("Invalid array size\n");
        exit(1);
    }
    if(size == MAX_DAYS + 1) {
        daysMonth[1]++;
    }
    arr = array_create(size, free_function);
    //printf("%ld\n", array_size(arr));
    if (array_size(arr) != size)
    {
        printf("Invalid array size\n");
        array_delete(arr);
        return;
    }

    for (size_t i = 0 ; i < array_size(arr); i++)
    {
        int *d = malloc(sizeof(int));
        *d = rand()%MAX_RAINFALL;
        array_set(arr, i, d);
    }
    //printArray(arr, nameMonth, daysMonth);
    //m = rainfallYear(arr, nameMonth, daysMonth, rainfallMonth);
    //printf("Precipitation per year: \n");
    for (size_t i = 0 ; i < m; i++)
    {
        printf("%d ", rainfallMonth[i]);
    }

}
