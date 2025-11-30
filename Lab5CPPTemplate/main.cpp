#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <algorithm>

#include "dataGenerator.h"
#include "stringContainer.h"

// Чтение файла для теста
std::vector<std::string> loadData(const std::string& filename) {
    std::vector<std::string> data;
    std::ifstream file(filename);
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line))
        {
            data.push_back(line);
        }

        file.close();
    }

    return data;
}

// Тестирование stringContainer
long long benchmarkStringContainer(const std::vector<std::string>& data) {
    StringContainer sc;
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& s : data) {
        sc.insert(s);
    }

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Тестирование стандартного std::set
long long benchmarkStdSet(const std::vector<std::string>& data) {
    std::set<std::string> stdSet;
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& s : data) {
        stdSet.insert(s);
    }

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

// Вывод результатов в табличном виде
void printResultsTable(
    const std::vector<size_t>& sizes,
    const std::vector<long long>& avlTimes,
    const std::vector<long long>& setTimes) {

    const int w_size = 15;
    const int w_time = 20;

    std::cout
        << std::setw(w_size) << "Items (N)" << " | "
        << std::setw(w_time) << "MyAVL Time (ms)" << " | "
        << std::setw(w_time) << "std::set Time (ms)" << std::endl;

    std::cout << std::string(w_size + w_time * 2 + 6, '-') << std::endl;
    for (size_t i = 0; i < sizes.size(); ++i) {
        std::cout
            << std::setw(w_size) << sizes[i] << " | "
            << std::setw(w_time) << avlTimes[i] << " | "
            << std::setw(w_time) << setTimes[i] << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    const std::vector<size_t> sizes = { 10000, 50000, 100000, 2000000 };
    std::vector<long long> avlTime;
    std::vector<long long> setTime;

    for (size_t n : sizes) {
        std::string filename = "bench_data_" + std::to_string(n) + ".txt";

        DataGenerator::generateFile(filename, n, DataMode::RANDOM);

        std::vector<std::string> data = loadData(filename);

        long long t1 = benchmarkStringContainer(data);
        long long t2 = benchmarkStdSet(data);

        avlTime.push_back(t1);
        setTime.push_back(t2);
    }

    printResultsTable(sizes, avlTime, setTime);
    return 0;
}
