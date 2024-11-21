#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include "array.h"

Array *array_create_and_read(std::ifstream& input)
{
    //std::cout << "acar"; //для дебага
    size_t n;
    int start;
    int end;

	if (!(input >> n) || n < 1) {
		std::cout << "Failed";
        return 0;
	}
    if (!(input >> start)) {
		std::cout << "Failed";
        return 0;
	}
    if (!(input >> end) || end < start) {
		std::cout << "Failed";
        return 0;
	}
	Array* arr = array_create(n);
	for (size_t i = 0; i < n; ++i) {
		int x = rand() % (end - start + 1) + start;
		array_set(arr, i, x);
	}
	return arr;
}

void task1(std::ifstream& input)
{
    //std::cout << "t1\n"; //для дебага
    Array* arr = array_create_and_read(input);
    size_t c5 = 0, c4 = 0, c3= 0, c2 = 0;

    for(int i =0 ; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
       if(array_get(arr, i) == 5) {c5++;}
       else if(array_get(arr, i) == 4) {c4++;}
       else if(array_get(arr, i) == 3) {c3++;}
       else if(array_get(arr, i) == 2) {c2++;}
    }

    std::cout << "\nколичество 5: " << c5 << "\nколичество 4: " << c4 << "\nколичество 3: " << c3 <<"\nколичество 2: " << c2;
}

void task2(std::ifstream& input)
{
    //std::cout << "t2\n"; //для дебага
    
    Array* arr = array_create_and_read(input);
    int start, end, counter = 0;
    if (!(input >> start)) {
		std::cout << "Failed";
        return;
	}
    if (!(input >> end || end < start)) {
		std::cout << "Failed";
        return;
	}
    
    for(int i =0 ; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
        int temp = array_get(arr, i);
        array_set(arr, i, 0);
        if( temp > end || temp < start) {
            array_set(arr, counter, temp);
            counter++;
        }
    }
    std::cout << "\n\n";
    for(int i =0 ; i < array_size(arr); i++) {
        std::cout << array_get(arr, i) << " ";
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    //std::cout << "Hello world";
    std::ifstream input("input.txt");
	if (input.is_open()) {

        std::cout << " task 1:\n";
	    task1(input);

        std::cout << "\n---------\n\n task 2:\n";
	    task2(input);
    }
	input.close();
    return 0;
}