#include <iostream>
#include <string>
#include <cstdlib>
#include "array.h"

#define MAX_DAYS 365
#define MAX_RAINFALL 1870

using namespace std;

void task1(Array *arr);


int main()
{
    Array *arr = NULL;
    /* Create array here */
    task1(arr);
    array_delete(arr);
}

void printArray(Array *arr, string nameMonth[12], size_t daysMonth[12]) {
    size_t m = 0, mD = 0;
    cout << "Array: \n";
    while(m != 12 && mD != array_size(arr)){
        cout << nameMonth[m] << " :\n";
        for (size_t i = 0 ; i < daysMonth[m] && mD != array_size(arr); i++)
        {
            cout << array_get(arr, mD) << " ";
            mD++;
            if(mD == array_size(arr) || i + 1  == daysMonth[m]) {
                cout << "[" << i+1 << "]\n";
            }
        }
        m++;
    }
}

size_t rainfallYear(Array *arr, string nameMonth[12], size_t daysMonth[12], int result[12]) {
    size_t m = 0, mD = 0;
    int sum;
    while(m != 12 && mD != array_size(arr)){
        sum = 0;
        for (size_t i = 0 ; i < daysMonth[m] && mD != array_size(arr); i++)
        {
            sum += array_get(arr, mD);
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
    string nameMonth[] = {"Jan", "Feb", "March", "April", "May", "June", "July", "August", "Sept", "Oct", "Nov", "Dec"};
    size_t size = 0, m = 0;
    int rainfallMonth[12];
    if (!(cin >> size) || size > MAX_DAYS + 1 || size < 1) {
        printf("Invalid array size\n");
        exit(1);
    }

    if(size == MAX_DAYS + 1) {
        daysMonth[1]++;
    }
    arr = array_create(size);
    if (array_size(arr) != size)
    {
        cout << "Invalid array size\n";
        array_delete(arr);
        return;
    }

    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, rand()%MAX_RAINFALL);
    }
    printArray(arr, nameMonth, daysMonth);
    m = rainfallYear(arr, nameMonth, daysMonth, rainfallMonth);
    cout << "Precipitation per year: \n";
    for (size_t i = 0 ; i < m; i++)
    {
        cout << rainfallMonth[i] << " ";
    }
    cout << endl;
}