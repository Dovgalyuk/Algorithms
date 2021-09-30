#include <iostream>
#include "array.h"

int main() {
    srand(time(NULL));
    size_t sizeArray;
    std::cout << "Input array size ";
    std::cin >> sizeArray;
    Array* arr = array_create(sizeArray);
    for (int i = 0; i < sizeArray; i++) {

        array_set(arr, i, 1 + rand() % 999);
        std::cout << "[" << i << "]=" <<array_get(arr,i);
        std::cout << std::endl;
    }
    int sum = 0;
    int digit;
    for (int i = 0; i < sizeArray; i++) {
        digit = array_get(arr, i);
        while (digit >= 10) {
            sum += digit % 10;
            digit /= 10;
        }
        sum+= digit;
    }
    std::cout << "The amount: " << sum;
    std::cout << std::endl;

	return 0;
}
