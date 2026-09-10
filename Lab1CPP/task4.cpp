#include <iostream>
#include <fstream>
#include "array.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Input file not specified";
        return 1;
    }

    std::ifstream input(argv[1]);
    if(!input){
        std::cout << "Failed!"; return 1;
    }
    size_t n; input>>n;
    Array *arr = array_create(n);
    for(size_t i = 0;i < n;++i){
        int value; input>>value; array_set(arr,i,value);
    }
    Array *positive = array_create(n);
    Array *negative = array_create(n);
    size_t poz_count = 0; size_t neg_count = 0;
    for(size_t i =0; i < n; ++i){
        int value = array_get(arr, i);
        if(value > 0){
            array_set(positive, poz_count, value);
            ++poz_count;
        }
        else if(value < 0){
            array_set(negative, neg_count, value);
            ++neg_count;
        }
    }
    std::cout << "Poz: ";
    for(size_t i =0; i < poz_count; ++i){
        std::cout << array_get(positive, i) << " ";
    }
    std::cout << "Neg: ";
    for(size_t i =0; i < neg_count; ++i){
        std::cout << array_get(negative, i) << " ";
    }
    std::cout << "\n";
    array_delete(arr);
    array_delete(positive);
    array_delete(negative);
}