#include <iostream>
#include "DynamicArray.h"

int main() {
    try {
        DynamicArray<int> numbers(5);

        for (std::size_t i = 0; i < numbers.getSize(); ++i) {
            numbers[i] = static_cast<int>(i + 1) * 10;
        }

        std::cout << "Размер массива: " << numbers.getSize() << "\n";
        std::cout << "Элементы: ";

        for (std::size_t i = 0; i < numbers.getSize(); ++i) {
            std::cout << numbers[i];

            if (i + 1 < numbers.getSize()) {
                std::cout << ' ';
            }
        }

        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
