#include <iostream>
#include <cstdlib>
#include "array.h"

int main(){
    srand(time(0));
    int sum_p = 0;
    int sum_n = 0;
    int count = 0;
    size_t size;

    std::cout << "Enter array size ";
    std::cin >> size;

    Array* array = array_create(size);

    for (size_t i = 0; i < size; i++)
    {
        array_set(array, i, rand() % 100 - 50);
        if (array_get(array, i) > 0) {
            sum_p += array_get(array, i);
            count++;
        }
        else
            sum_n += array_get(array, i);
    }

    if (count != 0)
        std::cout << "Average positive " << sum_p / count << '\n';
    if (size != count)
        std::cout << "Average negative " << sum_n / ((int)size - count);

    array_delete(array);
    return 0;
}