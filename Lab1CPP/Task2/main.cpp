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

void task2(Array *arr)
{
    int size = array_size(arr);

    if (size < 5)
    {
        cout << "Массив меньше пяти элементов." << endl;
        return;
    }

    int sum = 0;

    for (int i = 0; i < 5; ++i)
        sum += array_get(arr, i);

    int max = sum;
    
    for (int i = 5; i < size; ++i)
    {
        sum += array_get(arr, i) - array_get(arr, i - 5);
        if (sum > max)
        {
            max = sum;
        }
    }

    cout << "Максимальная сумма пяти соседних элементов: " << max << endl;
}

int main(int argc, char **argv) 
{
    Array *arr = NULL;
    ifstream input(argv[1]);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    
    return 0;
}
