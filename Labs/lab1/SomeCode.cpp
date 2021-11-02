#include <iostream>
#include "array.h"
#include <stdlib.h>
const int decade = 10;


void forecast(Array* arr) {
    int sum = 0;
    int c = 1;
    for (int j = 0; j < array_size(arr); j++) {
        sum += array_get(arr, j);
        if (((j + 1) % decade) == 0) {
            std::cout << "decade " << c << ": " << sum / decade << std::endl;
            sum = 0;
            c++;
        }
    }

}

int main()
{
    int size = 0;
    srand(time(0));
    std::cout << "write down size of array" << std::endl;
    std::cin >> size;
    Array* arr = array_create(size);
    for (int i = 0; i < size; i++) {
        array_set(arr, i, 1 + rand() % 100);
    }

    forecast(arr);
    array_delete(arr);
}
