#include <iostream>
#include <fstream>
#include "array.h"
#include "reader.h"
#include "task1.h"

int main() {
    std::ifstream input("input.txt");
    Array *arr = read_file_and_create_array(input);
    input.close();

    double res_task1 = task1(arr);

    array_delete(arr);

    std::ofstream output("output.txt");
    if (output.is_open()) {
        output << res_task1 << '\n';
        output.close();
    }

    return 0;
}