#include <fstream>
#include <iostream>
#include "DynamicArray.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: max_five_sum <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input) {
        std::cerr << "Не удалось открыть файл\n";
        return 1;
    }

    int n;
    input >> n;

    if (!input || n < 5) {
        std::cerr << "Размер массива должен быть не меньше 5\n";
        return 1;
    }

    DynamicArray<int> numbers(n);

    for (int i = 0; i < n; ++i) {
        if (!(input >> numbers[i])) {
            std::cerr << "Недостаточно данных в файле\n";
            return 1;
        }
    }

    long long currentSum = 0;

    for (int i = 0; i < 5; ++i) {
        currentSum += numbers[i];
    }

    long long maxSum = currentSum;
    int bestStart = 0;

    for (int i = 5; i < n; ++i) {
        currentSum = currentSum - numbers[i - 5] + numbers[i];

        if (currentSum > maxSum) {
            maxSum = currentSum;
            bestStart = i - 4;
        }
    }

    std::cout << "Максимальная сумма: " << maxSum << "\n";
    std::cout << "Позиции пяти элементов: "
              << bestStart + 1 << "-" << bestStart + 5 << "\n";

    std::cout << "Элементы: ";

    for (int i = bestStart; i < bestStart + 5; ++i) {
        std::cout << numbers[i];

        if (i + 1 < bestStart + 5) {
            std::cout << ' ';
        }
    }

    std::cout << "\n";

    return 0;
}
