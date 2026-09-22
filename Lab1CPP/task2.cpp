#include <iostream>
#include <cmath>
#include "array.h"

void task2(Array* arr)
{
    for (size_t i = 0; i < arr->size(); i++) {
        int elem = arr->get(i);
        if (elem) {
            bool can_divide = 0;
            for (int k = 0; k < arr->size(); k++) {
                if (!(arr->get(k)) || (elem == arr->get(k))) continue;
                if (!(elem % arr->get(k))) {
                    can_divide = 1;
                    break;
                }
            }
            if (!can_divide) std::cout << elem << " ";
        }
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    FILE* input = fopen(argv[1], "r");
    Array* arr = NULL;
    arr = array_create_and_read(input);
    task2(arr);
    delete arr;
    fclose(input);
}