#include <array.h>
#include <iostream>
#include <fstream>

double task_1(Array*& array, std::ifstream& input) {
    int size;
    input >> size;

    array = array_create(size);

    for (int i = 0; i < size; ++i) {
        Data value;
        input >> value;
        array_set(array, i, value);
    }

    Data sum = 0;
    int count = 0;
    for (size_t i = 0; i < array_size(array); i++) {
        Data value = array_get(array, i);
        if (value > 10) {
            sum += value;
            ++count;
        }
    }

    double avg = count > 0 ? static_cast<double>(sum) / count : 0;

    std::cout << "Average of elements > 10: " << avg << std::endl;

    return avg;
}

void task_2(Array*& array) {
    if (array_size(array) < 5) {
        std::cerr << "Ошибка: размер массива должен быть не менее 5." << std::endl;
        return;
    }

    Data max_sum = 0;
    size_t start_index = 0;

    for (size_t i = 0; i < 5; i++) {
        max_sum += array_get(array, i);
    }

    Data current_sum = max_sum;
    for (size_t i = 5; i < array_size(array); i++) {
        current_sum = current_sum - array_get(array, i - 5) + array_get(array, i);
        if (current_sum > max_sum) {
            max_sum = current_sum;
            start_index = i - 4;
        }
    }

    for (size_t i = start_index; i < start_index + 5; i++) {
        std::cout << "Index: " << i << ", Value: " << array_get(array, i) << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);

    if (input.is_open()) {
        Array* array = nullptr;

        task_1(array, input);
        task_2(array);

        array_delete(array);

        input.close();
    } else {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    return 0;
}