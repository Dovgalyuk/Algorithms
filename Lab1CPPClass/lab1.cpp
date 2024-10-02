#include <stdio.h>
#include "array.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

Array *new_array(std::ifstream& input)
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

Array* array_with_random(std::ifstream& input, int start, int end) {
    size_t n;
    input >> n;

    Array* arr = new Array(n);

    for (size_t i = 0; i < n; ++i) {
        int ran_number = start + rand() % (start - end + 1);
        arr->set(i, ran_number);
    }
    return arr;
}

void task1(const Array& arr, std::ofstream& output)
{
    int counter = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        int divisibility_test = arr.get(i);
        for (int j = 2; j < 10; j+=1) {
            if (divisibility_test%j==0) {
            counter +=1;
            }
        }
    }
    output << "Number of divisidle numbers from 2 to 9:" << counter << std::endl;
}

void task2(Array& arr, int a, int b, std::ofstream& output)
{
    int counter = 0;
    for (size_t i = 0;i < arr.size(); ++i) {
        if (arr.get(i)>= a && arr.get(i) <= b) {
            for (size_t j = i; j <arr.size()-1; ++j) {
                arr.set(j,arr.get(i+1));
            }
            arr.set(arr.size()-counter-1,0);
            counter+=1;
        }
    }
    for (size_t i = 0;i <arr.size();++i) {
        output << arr.get(i) << std::endl;
    }
}

int main(int argc, char **argv)
{
    //No random
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    if (!input.is_open()) {
        std::cerr << "The file couldn't be opened: " << argv[1] << std::endl;
        return 1;
    }
    Array* arr = new_array(input);

    task1(*arr, output);

    delete arr;

    int a,b; input >> a >> b;
    arr = new_array(input);
    task2(*arr, a, b, output);
    delete arr;

    input.close();

    //With random
    std::srand(std::time(nullptr));
    std::ifstream random(argv[3]);
    if (!random.is_open()) {
        std::cerr << "The file couldn't be opened: " << argv[3] << std::endl;
        return 1;
    }

    arr = array_with_random(random, -100, 100);
    task1(*arr, output);
    delete arr;

    arr = array_with_random(random, -100, 100);
    task2(*arr, a, b, output);
    delete arr;

    random.close();

}
