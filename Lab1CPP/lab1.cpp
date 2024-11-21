#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "../LibraryCPP/array.h"

using namespace std; 

Array *array_create_and_read(ifstream& input){
    if (!input) {
        cerr << "Couldn't open this file." <<  endl;
        return nullptr;
    }

    size_t new_size;
    input >> new_size;

    Array *arr = array_create(new_size);
    if (!arr){
        return nullptr;
    } 

    for (size_t i = 0; i < new_size; ++i) {
        int number;
        if (!(input >> number)) {
            cerr << "Couldn't read number from file." << endl;
            array_delete(arr);
            return nullptr;
        }
        array_set(arr, i, number);
    }
    return arr;
}

void task1(ifstream& input) {
    Array* arr = array_create_and_read(input);
    int max = 0;
    int counter = 0;
    for(size_t i = 0; i<array_size(arr); i++){
        int num = array_get(arr, i);
        if(num>max){
            max = num;
        }
    }

    for(size_t i = 0;i<array_size(arr);i++){
        int abs_num = array_get(arr, i);
        if(abs(abs_num)>max){
            counter+=1;
        }
    }

    cout << "Result: " << counter;
}

void task2(ifstream& input) {
    Array* arr = array_create_and_read(input);
    int a;
    int b;

    input >> a;
    input >> b;

    size_t index = 0;

    for (size_t i = 0; i < array_size(arr); ++i) {
        int num = array_get(arr, i);

        if (num < a || num > b) {
            array_set(arr, index++, array_get(arr,i));
        }
    }

    while (index < array_size(arr)) {
        array_set(arr, index++, 0);
    }

    cout << endl;

    for (size_t i = 0; i < array_size(arr); i++){
        cout << array_get(arr, i) << ' ';
    }

}

int main(int argc, char *argv[]) {

    // ifstream input("test.txt");
    // if (input.is_open())
    // {
    //     task1(input);
    //     task2(input);
    // }
    // input.close();
    // return 0;


    if (argc < 2) {
        cerr << "Usage: " << argv[0] << "<input_file>" << endl;
        return 1; 
    }

    ifstream input(argv[1]); 
    if (input.is_open()) {
        task1(input);
        task2(input);
    } else {
        cerr << "Couldn't open this file." << endl;
        return 1;
    }

    input.close();
    return 0;
}