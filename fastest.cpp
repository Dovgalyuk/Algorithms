#include <fstream>
#include <iostream>
#include "DynamicArray.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: fastest <input_file>\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input) {
        std::cerr << "Не удалось открыть файл\n";
        return 1;
    }

    int n;
    input >> n;

    if (!input || n <= 0) {
        std::cerr << "Неверный размер массива\n";
        return 1;
    }

    DynamicArray<int> speed(n);

    for (int i = 0; i < n; ++i) {
        if (!(input >> speed[i])) {
            std::cerr << "Недостаточно данных в файле\n";
            return 1;
        }
    }

    int maxSpeed = speed[0];
    int first = 0;
    int last = 0;

    for (int i = 1; i < n; ++i) {
        if (speed[i] > maxSpeed) {
            maxSpeed = speed[i];
            first = i;
            last = i;
        }
        else if (speed[i] == maxSpeed) {
            last = i;
        }
    }

    std::cout << "Максимальная скорость: " << maxSpeed << "\n";
    std::cout << "Номер первого автомобиля: " << first + 1 << "\n";
    std::cout << "Номер последнего автомобиля: " << last + 1 << "\n";

    return 0;
}
