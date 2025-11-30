#ifndef DATA_GENERATOR_TEMPLATE_H
#define DATA_GENERATOR_TEMPLATE_H

#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include <iostream>
#include <iomanip>

enum class DataMode {
    RANDOM,
    SORTED
};

class DataGenerator {
public:
    static void generateFile(
        const std::string& filename, size_t count,
        DataMode mode, size_t strLen = 10)
    {
        std::vector<std::string> dataset;
        dataset.reserve(count);

        std::mt19937 rng(std::random_device{}());

        // Генерация данных
        for (size_t i = 0; i < count; ++i) {
            dataset.push_back(generateRandomString(strLen, rng));
        }

        // Отсортированный набор (для проверки вырождения дерева O(N*N))
        if (mode == DataMode::SORTED) {
            std::sort(dataset.begin(), dataset.end());
        }

        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Can not open file " << filename << " for write." << std::endl;
            return;
        }

        for (const auto& str : dataset) {
            outFile << str << '\n';
        }

        outFile.close();
    }

private:
    static std::string generateRandomString(size_t length, std::mt19937& rng) {
        static const char charset[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

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