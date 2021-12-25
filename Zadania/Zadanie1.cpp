#include <iostream>
#include "array.h"
#include <ctime>

int main() {
    std::cout<<"array size: ";
    int size;
    std::cin>>size;
    Array *arr = array_create(size);

    std::srand(time(0));
    for (size_t i = 0; i < array_size(arr); i++) {
        array_set(arr, i, std::rand()%100);
    }
    std::cout << "\ngenerated array:\n";
    for (size_t i = 0; i < array_size(arr); i++) {
        std::cout<<array_get(arr, i) << " ";
    }

    for (size_t i = 0; i < array_size(arr)-1; i+=2) {
        int t = array_get(arr, i);
        array_set(arr, i, array_get(arr, i+1));
        array_set(arr, i+1, t);
    }
    std::cout << "\nprocessed array:\n";
    for (size_t i = 0; i < array_size(arr); i++) {
        std::cout<<array_get(arr, i) << " ";
    }
    

}