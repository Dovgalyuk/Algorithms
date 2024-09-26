#include <stdio.h>
#include "array.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Array *array_create_and_read(std::ifstream& input)
{
    size_t n;
    input >> n;

    Array* arr = new Array(n); 

    for (size_t i = 0; i < n; ++i)
    {
        int number;
        input >> number;
        arr->set(i, number); 
    }
    return arr;
}

bool check_output(std::ifstream& output, const Array& arr) {
    for(size_t i = 0; i < arr.size(); i++) {
        int number; 
        output >> number;
        if(number != arr.get(i)) {
            return false;
        }
    }
    return true;
}

Array* array_create_random_number(std::ifstream& input, int start, int end) {
    size_t n;
    input >> n;

    Array* arr = new Array(n);

    for (size_t i = 0; i < n; ++i) {
        int ran_number = start + rand() % (start - end + 1);
        arr->set(i, ran_number);
    }
    return arr;
}

void task1(const Array& arr)
{
    int counter = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        int divisibility_test = arr.get(i);
        for (int j = 1; j < 10; j+=1) {
            if (divisibility_test%j==0) {
            counter +=1;
            }
        }
    }
    std::cout << "Number of divisidle numbers from 2 to 9:" << counter << std::endl;
}

void task2(Array *arr)
{
    
}

int main(int argc, char **argv)
{
    std::srand(std::time(nullptr));

    std::ifstream input(argv[1]);
    std::ifstream output(argv[2]);
    if (!input.is_open()) {
        std::cerr << "The file couldn't be opened: " << argv[1] << std::endl;
        return 1;
    }
    Array* arr = array_create_and_read(input);

    task1(*arr);
    delete arr;

    //int a,b; input >> a >> b;
    //arr = array_create_and_read(input);
    //task2(*arr);
    //delete arr;

    input.close();

}
