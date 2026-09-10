#include <iostream>
#include <fstream>
#include "array.h"
#include "reader.h"
#include "task2.h"

int main() {
    std::ifstream input("input.txt");
    Array *arr = read_file_and_create_array(input);
    input.close();

    size_t res = task2(arr);

    std::ofstream output("output.txt");
    if (output.is_open()) {
        for (size_t i = 0; i < 5; i++) {
            output << array_get(arr, res);

            if (i != 4) {
                output << " ";
            }

            res++;
        }
    }
    output.close();
    array_delete(arr);

    return 0;
}