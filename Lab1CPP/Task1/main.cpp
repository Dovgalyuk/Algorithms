#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream &input) 
{
    int n;
    input >> n;
    Array *arr = array_create(n);

    for (int i = 0; i < n; ++i) 
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }

    return arr;
}

void task1(Array *arr) 
{
    double sum = 0;
    int day = 0;
    int size = array_size(arr);

    for (int i = 0; i < size; ++i) 
    {
        int rain = array_get(arr, i);
        if (rain > 0) 
        {
            sum += rain;
            ++day;
        }
    }

    if (day == 0) 
    {
        cout << "Дождливых дней не было." << endl;
    } 
    else 
    {
        cout << "Среднее количество осадков: " << sum / day << endl;
    }
}

int main(int argc, char **argv) 
{
    Array *arr = NULL;
    ifstream input(argv[1]);

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    
    return 0;
}
