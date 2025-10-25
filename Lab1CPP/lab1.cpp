#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; i++)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}


void task1(Array *arr)
{
    if (array_size(arr) == 0)
        return;

    Data min = array_get(arr, 0);
    Data max = array_get(arr, 0);
    
    for (size_t i = 1; i < array_size(arr); i++) {
        Data num = array_get(arr, i);
        if (num < min) min = num;
        if (num > max) max = num;
    }

    double min_max = (min + max) / 2.0;
    int counter = 0;

    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) > min_max) {
            counter++;
        }
    }

    cout << "amount of numbers: " << counter << "\n";
        cout << "numbers:" << "\n";

    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) > min_max) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
}

void task2(Array *arr)
{
    if (array_size(arr) == 0)
    return;

    int max_repeat = 0;
    Data popular_num = array_get(arr, 0);

    for (size_t i = 0; i < array_size(arr); ++i) {
        int counter = 0;
        Data num = array_get(arr, i);
        
        for (size_t j = 0; j < array_size(arr); ++j) {
            if (array_get(arr, j) == num) {
                counter++;
            }
        }
        
        if (counter > max_repeat) {
            max_repeat = counter;
            popular_num = num;
        }
    }

    cout << "most frequent: " << popular_num << endl;
    cout << "frequency: " << max_repeat << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        return 1;
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        return 1;
    }

    Array *arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);
    /* Create another array here */
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}
