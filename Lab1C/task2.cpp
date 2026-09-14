#include <fstream>
#include <iostream>
#include "array.h"

Array* array_create_and_read(std::ifstream& input)
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

void task2(Array* arr)
{
    if (!arr) return;
    size_t n = array_size(arr);
    int raznica = -1, vr_raznica;
    for (int i = 0; i < n; i++) {
        if (array_get(arr, i) % 2 != 0) continue;
        for (int j = i + 1; j < n; j++) {
            if (array_get(arr, j) % 2 != 0) continue;
            if (array_get(arr, i) == array_get(arr, j)) continue;
            vr_raznica = array_get(arr, i) - array_get(arr, j);
            if (vr_raznica < 0) vr_raznica = -vr_raznica;
            if (raznica == -1 || vr_raznica < raznica) {
                raznica = vr_raznica;
            }
        }
    }
    std::cout << raznica;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    std::ifstream input(argv[1]);
    if (!input.is_open()) {
        return 1;
    }
    Array* arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);
    input.close();
    return 0;
}