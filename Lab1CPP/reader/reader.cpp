#include "reader.h"

Array *read_file_and_create_array(std::ifstream &file) {
    size_t count;
    file >> count;

    Array *arr = array_create(count);

    double number;
    for (size_t i = 0; i < count; i++){
        if (file >> number) {
            array_set(arr, i, number);
        }
    }
    return arr;
}