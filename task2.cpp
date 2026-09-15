#include "Array.hpp"
#include <fstream>
#include <iostream>

// Читает последовательность чисел, сжимает одинаковые значения и сохраняет результат.
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: task2 <input_file> <output_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Ошибка при открытии файла\n";
        return 1;
    }

    size_t count;
    if (!(input >> count) || count == 0) {
        return 0; // Пустой массив или ошибка ввода
    }

    // Заполняем массив
    arr<int> values(count);
    for (size_t i = 0; i < count; ++i) {
        input >> values[i];
    }

    // Сжатие RLE: один понятный цикл
    size_t repetitions = 1;
    for (size_t i = 1; i < values.size(); ++i) {
        if (values[i] == values[i - 1]) {
            ++repetitions;
        } else {
            output << values[i - 1] << ' ' << repetitions << '\n';
            repetitions = 1;
        }
    }
    // Выводим последний элемент и его повторы
    output << values[values.size() - 1] << ' ' << repetitions << '\n';

    return 0;
}