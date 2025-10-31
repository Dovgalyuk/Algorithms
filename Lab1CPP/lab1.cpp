#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;

Array *array_create_and_read(ifstream &input)
{
    int n;
    input >> n;

    Array *arr = array_create(n);

    for(int i = 0; i < n; i++)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array *arr)
{
    if (array_size(arr) == 0) {
        return;
    }

    Data min = array_get(arr, 0);
    Data max = array_get(arr, 0);

   
    for (size_t i = 1; i < array_size(arr); i++) {
        Data current = array_get(arr, i);
        if (current < min) min = current;
        if (current > max) max = current;
    }

    double average = (min + max) / 2.0;
    int count = 0;


    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i);
        if (i != array_size(arr) - 1) {
            cout << " ";
        }
    }
    cout << endl;


    cout << min << " " << max << " " << average << endl;

    for (size_t i = 0; i < array_size(arr); i++) {
        if (array_get(arr, i) < average) {
            cout << i;
            count++;
            // Добавляем пробел если это не последний элемент
            if (i != array_size(arr) - 1) {
                cout << " ";
            }
        }
    }
    cout << endl << count << endl;
}

void task2(Array *arr)
{
    if (array_size(arr) == 0) {
        return;
    }

    for (size_t i = 0; i < array_size(arr); i++) {
        cout << array_get(arr, i) << " ";
    }

 
    for (size_t i = 0; i < array_size(arr); i++) {
        int count = 0;
        bool already_counted = false;

        for (size_t k = 0; k < i; k++) {
            if (array_get(arr, k) == array_get(arr, i)) {
                already_counted = true;
                break;
            }
        }

        if (!already_counted) {
            for (size_t j = 0; j < array_size(arr); j++) {
                if (array_get(arr, i) == array_get(arr, j)) {
                    count++;
                }
            }

            if (count == 2) {
                cout << array_get(arr, i) << " ";
               
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << argv[0] << endl;
        return 1;
    }


    Array *arr = NULL;
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << argv[1] << endl;
        return 1;
    }

    arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}