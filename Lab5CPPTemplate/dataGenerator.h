#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <random>

class DataGenerator {
public:
    // Генерирует файл с заданным количеством (count) случайных строк
    static void generateFile(const std::string& filename, size_t count, size_t strLen = 10) {
        std::vector<std::string> dataset;
        dataset.reserve(count);

        // Инициализация генератора случайных чисел
        std::mt19937 rng(std::random_device{}());

        // Заполнение вектора случайными строками
        for (size_t i = 0; i < count; ++i) {
            dataset.push_back(generateRandomString(strLen, rng));
        }

        // Открытие файла для записи
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Can not open file " << filename << " for write." << std::endl;
            return;
        }

        // Построчная запись данных в файл
        for (const auto& str : dataset) {
            outFile << str << '\n';
        }

        outFile.close();
    }

private:
    // Создает одну случайную строку заданной длины, используя переданный генератор
    static std::string generateRandomString(size_t length, std::mt19937& rng) {
        static const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

        // Равномерное распределение для выбора случайного индекса из charset
        // sizeof(charset) - 2 исключает нуль-терминатор строки
        std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);
        std::string s;
        s.reserve(length);

        for (size_t i = 0; i < length; ++i) {
            s += charset[dist(rng)];
        }

        return s;
    }
};

#endif