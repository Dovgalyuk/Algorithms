#include "array.h"
#include <iostream>
#include <limits>

void task1(const std::string& input)
{
	int a, b;
	input >> a >> b;
    Array* arr = array_create_and_read(input);


    int sum = 0;
    for (size_t i = 0; i < array_size(arr); ++i) {
        int value = array_get(arr, i);
        if (value % a == 0 || value % b == 0) {
            sum += value;
        }
    }

    std::cout << "Сумму элементов массива, кратных a или b: " << sum << std::endl;

    array_delete(arr);

}


void task2(const std::string& input) {

	Array* arr = array_create_and_read(input);

    int max_sum = std::numeric_limits<int>::min();
    size_t best_start_index = 0;

    for (size_t i = 0; i <= array_size(arr) - 5; ++i) {
        int current_sum = 0;

        for (size_t j = 0; j < 5; ++j) {
            current_sum += array_get(arr, i + j);
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
            best_start_index = i;
        }
    }

    
    std::cout << "Пять соседних элементов с максимальной суммой:" ;
    for (size_t j = 0; j < 5; ++j) {
        std::cout << array_get(arr, best_start_index + j) << " ";
    }
    std::cout << std::endl;

    array_delete(arr);

}

int main() {
    const std::string file = "input.txt";

	task1(file);
	task2(file);


	return 0;
}