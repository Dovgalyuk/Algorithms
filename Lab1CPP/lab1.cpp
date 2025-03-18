#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "array.h"

size_t find_max_odd_segment(const Array* arr) {
    size_t max_length = 0;
    size_t current_length = 0;

    for (size_t i = 0; i < array_size(arr); ++i) {
        if (array_get(arr, i) % 2 != 0) {
            current_length++;
            if (current_length > max_length) {
                max_length = current_length;
            }
        } else {
            current_length = 0;
        }
    }

    return max_length;
}

void compress_array(Array* arr, int a, int b) {
    size_t write_index = 0;

    for (size_t read_index = 0; read_index < array_size(arr); ++read_index) {
        int value = array_get(arr, read_index);
        if (value < a || value > b) {
            array_set(arr, write_index, value);
            write_index++;
        }
    }

    for (size_t i = write_index; i < array_size(arr); ++i) {
        array_set(arr, i, 0);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "�������������: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()) {
        std::cerr << "������: �� ������� ������� ���� " << argv[1] << std::endl;
        return 1;
    }

    size_t size;
    int a, b;
    input_file >> size >> a >> b;

    Array* arr = array_create(size);
    std::srand(std::time(nullptr));
    for (size_t i = 0; i < size; ++i) {
        array_set(arr, i, std::rand() % 100);
    }

    std::cout << "�������� ������: ";
    for (size_t i = 0; i < array_size(arr); ++i) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;

    size_t max_odd_length = find_max_odd_segment(arr);
    std::cout << "������������ ����� ������� �� �������� �����: " << max_odd_length << std::endl;

    compress_array(arr, a, b);

    std::cout << "������ ������: ";
    for (size_t i = 0; i < array_size(arr); ++i) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << std::endl;

    array_delete(arr);

    return 0;
}