#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

#include "huffmanArchiv.h"


// Функция для запуска одного теста архивации
void run_test(const std::string& test_name, const std::string& input_data) {
    std::cout << "TEST " << test_name << "\n";

    HuffmanArchiv archive;

    std::stringstream source(input_data);
    std::stringstream compressed;
    std::stringstream restored;

    // Сжатие
    archive.compress(source, compressed);

    // Распаковка
    compressed.seekg(0);
    archive.decompress(compressed, restored);

    // Проверка
    std::string result = restored.str();

    if (input_data == result) {
        std::cout << "OK\n";
    }
    else {
        std::cout << "Fail\n";
        exit(1);
    }
}

int main(int argc, char const* argv[])
{
    std::cout << "===  Run Huffman Functiona Tests ===\n";

    // Тест 1: Обычная строка
    run_test("Simple string", "Hello, World");

    // Тест 2: Пустая строка
    run_test("Empty string", "");

    // Тест 3: Строка из одинаковых символов
    run_test("Repeat chars", "AAAAAAAAAAAAAAAAAA");

    std::cout << "=== All tests passed ===\n";
    return 0;
}
