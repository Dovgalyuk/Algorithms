#include <iostream>
#include <fstream>
#include "array.h"
#include "reader.h"

double task1(Array *arr, size_t count) {
    double elect_cond = 0;

    for (size_t i = 0; i < count; i++) {
        double val = array_get(arr, i);

        if (val != 0) {
            elect_cond += (1.0/val);
        }
    }

    if (elect_cond == 0) return 0;

    return 1.0/elect_cond;

}

int main() {
    std::ifstream input("input.txt");
    Array *arr = read_file_and_create_array(input);
    input.close();

    double res_task1 = task1(arr, array_size(arr));

    array_delete(arr);

    std::ofstream output("output.txt");
    if (output.is_open()) {
        output << res_task1 << '\n';
        output.close();
    }

    return 0;
}