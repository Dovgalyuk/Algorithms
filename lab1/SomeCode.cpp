#include <iostream>

#include "array.h"
int decade = 10;
int sum = 0;
int size = 0;

void forecast(Array *arr) {  
    int j = 20;
    int c = 3;
    for (int i = 0; i < 3; i++) {
        for (j; j < size; j++) {
            sum += array_get(arr, j);
        }
        std::cout << "decade " << c << ": " << sum / decade << std::endl;
        c--;
        j -= 20;
        size -= 10;
        sum = 0;
    }
}

int main()
{
    srand(time(0));
    std::cout << "write down size of array" << std::endl;
    std::cin >> size;

    Array *arr = array_create(size);
    for (int i = 0; i < size; i++) {
        array_set(arr, i, 1 + rand() % 100);
    }
    forecast(arr);
}
