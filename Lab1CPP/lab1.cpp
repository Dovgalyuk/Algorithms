#include <iostream>
#include <fstream>
#include <string>
#include "array.h"

using namespace std;

Array* array_create_and_write(ifstream& input)
{
    int n;
    input >> n;
    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (int i = 0; i < n; ++i)
    {
        int x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

void task1(Array* arr)
{
    if (!arr) return;
    size_t size = array_size(arr);
    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        int value = array_get(arr, i);
        for (int d = 2; d <= 9; ++d) {
            if (value % d == 0) {
                count++;
                break;
            }
        }
    }
    cout << count << endl;
}

void task2(Array* arr)
{
    size_t size = array_size(arr);
    if (size < 5) return;
    int max_sum = 0;
    size_t max_index = 0;
    for (size_t i = 0; i < 5; ++i) max_sum += array_get(arr, i);

    int cur_sum = max_sum;
    for (size_t i = 1; i <= size - 5; ++i) {
        cur_sum = cur_sum - array_get(arr, i - 1) + array_get(arr, i + 4);
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
            max_index = i;
        }
    }
    for (size_t i = 0; i < 5; ++i) {
        cout << array_get(arr, max_index + i) << (i < 4 ? " " : "\n");
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }

    ifstream input(argv[1]);;

    Array* arr = array_create_and_write(input);

    task1(arr);
    array_delete(arr);

    /* Create another array here */
    arr = array_create_and_write(input);

    task2(arr);
    array_delete(arr);
    input.close();
}