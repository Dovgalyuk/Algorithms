#include <iostream>
#include "array.h"

void fill_arr(Array *arr) {   //fill array with students heighst
    std::srand(532);
    for (size_t i = 0; i < array_size(arr); i++) {
        int h = std::rand()%40 + 150;
        array_set(arr, i, h);
    }
}
void print_arr(Array *arr) {
    for (size_t i = 0; i < array_size(arr); i++) {
        std::cout<<array_get(arr, i);
        std::cout<<" ";
    }
    std::cout<<std::endl;
}
int count_higher_than_average_students(Array *arr) {
    int avg = 0;
    for (size_t i = 0; i < array_size(arr); i++) {
        avg += array_get(arr, i);
    }
    avg /= array_size(arr);
    int count = 0;
    for (size_t i = 0; i < array_size(arr); i++) {
        int h = array_get(arr, i);
        if (h > avg) 
            count++;
    }
    return count;
}
int main() {
    std::cout<<"array size: ";
    int size;
    std::cin>>size;
    Array *arr = array_create(size);
    fill_arr(arr);
    std::cout<<"array generated: \n";
    print_arr(arr);
    std::cout<< count_higher_than_average_students(arr) 
        << " students are above average tall\n";
    system("pause");
    array_delete(arr);
}