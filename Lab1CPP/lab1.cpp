
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstddef>

#include "array.h"

using namespace std;

void print_array(const Array* arr)
{
    for (size_t i = 0; i < array_size(arr); ++i)
    {
        if (i > 0){
            cout << " ";
        }
        cout << array_get(arr, i);
    }
    cout << endl;
}

void task1(ifstream& input)
{
    size_t n;
    if (!(input >> n)) {
        cerr << "Ошибка чтения размера массива" << endl;
        return;
    }
    Array* arr = array_create(n);

    for (size_t i = 0; i < n; ++i) {
        array_set(arr, i, static_cast<int>(i + 1));
    }

    bool* is_prime = new bool[n + 1];

    for (size_t i = 0; i <= n; ++i) {
        is_prime[i] = true;
    }
    if (n >= 0) {
        is_prime[0] = false;
    }

    if (n >= 1) {
        is_prime[1] = false;
    }


    for (size_t p = 2; p * p <= n; ++p){
        if (is_prime[p]){
            for (size_t j = p * p; j <= n; j += p){
                is_prime[j] = false;
            }
        }
    }

    size_t position = 0;

    for (size_t number = 2; number <= n; ++number){
        if (is_prime[number]){
            array_set(
                arr,
                position,
                static_cast<int>(number)
            );
            ++position;
        }
    }

    while (position < n){
        array_set(arr, position, 0);
        ++position;
    }

    print_array(arr);

    delete[] is_prime;
    array_delete(arr);
}

void task2(ifstream& input){
    size_t n;

    if (!(input >> n)){
        cerr << "Ошибка чтения размера массива" << endl;
        return;
    }

    Array* arr = array_create(n);


    for (size_t i = 0; i < n; ++i){
        Data value;

        if (!(input >> value))
        {
            cerr << "Недостаточно элементов в файле" << endl;

            array_delete(arr);
            return;
        }

        array_set(arr, i, value);
    }

    Data* even = new Data[n];
    size_t even_count = 0;

    for (size_t i = 0; i < n; ++i){
        Data value = array_get(arr, i);

        if (value % 2 == 0){
            even[even_count] = value;
            ++even_count;
        }
    }

    if (even_count < 2){
        cout << "NO DIFFERENT EVEN ELEMENTS" << endl;

        delete[] even;
        array_delete(arr);
        return;
    }

    sort(even, even + even_count);

    bool found = false;
    Data min_difference = 0;

    for (size_t i = 1; i < even_count; ++i){
        if (even[i] != even[i - 1]){
            Data difference = even[i] - even[i - 1];

            if (!found || difference < min_difference){
                min_difference = difference;
                found = true;
            }
        }
    }


    if (found){
        cout << min_difference << endl;
    }
    else{
        cout << "NO DIFFERENT EVEN ELEMENTS" << endl;
    }

    delete[] even;
    array_delete(arr);
}


int main() {
    ifstream input("input.txt");

    if (!input){
        cerr << "Не удалось открыть input.txt" << endl;
        return 1;
    }
    task1(input);

    task2(input);

    return 0;
}

