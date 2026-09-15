#include "Array.hpp"
#include <fstream>
#include <iostream>

// Читает оценки из файла, подсчитывает их количество и записывает результат.
int main(int argc, char* argv[]) {
    // 1. Проверяем аргументы командной строки
    if (argc < 3) {
        std::cerr << "Usage: task1 <input_file> <output_file>\n";
        return 1;
    }

    // 2. Открываем файлы
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files\n";
        return 1;
    }

    // 3. Читаем количество элементов
    size_t count;
    if (!(input >> count)) {
        return 1;
    }

    // 4. Создаём массив и заполняем его
    arr<int> marks(count);
    for (size_t i = 0; i < count; ++i) {
        input >> marks[i];
    }

    // 5. Обрабатываем данные из массива
    int twos = 0, threes = 0, fours = 0, fives = 0;
    for (size_t i = 0; i < marks.size(); ++i) {
        if (marks[i] == 2) ++twos;
        else if (marks[i] == 3) ++threes;
        else if (marks[i] == 4) ++fours;
        else if (marks[i] == 5) ++fives;
    }

    // 6. Выводим результат
    output << "5: " << fives << '\n';
    output << "4: " << fours << '\n';
    output << "3: " << threes << '\n';
    output << "2: " << twos << '\n';

    return 0;
}