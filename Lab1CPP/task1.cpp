#include <iostream>
#include <cmath>
#include "array.h"


void task1(Array *arr)
{
    int sum = 0;
    for (int i = 0; i < arr->size(); i++)
        sum += arr->get(i);
    double average = sum / double(arr->size());
    double dif(sum);
    int closest = 0;
    for (int i = 0; i < arr->size(); i++) {
        double tmp = std::abs(average - arr->get(i));
        if (dif > tmp) {
            dif = tmp;
            closest = arr->get(i);
            if (!dif)
                break;
        }
    }
    std::cout << closest << std::endl;
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return 1;
    }
    FILE* input = fopen(argv[1], "r");
    Array *arr = NULL;
    arr = array_create_and_read(input);
    task1(arr);
    delete arr;
    fclose(input);
}
