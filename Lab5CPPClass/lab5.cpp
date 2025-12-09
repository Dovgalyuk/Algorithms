#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <random>
#include <fstream>
#include "splay_tree.h"

// генератор входных данных
std::string random_string(size_t length) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string s;
    s.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        s += alphanum[rand() % (static_cast<int>(sizeof(alphanum) - 1))];
    }
    return s;
}

std::vector<std::string> generate_data(size_t count) {
    std::vector<std::string> data;
    data.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        data.push_back(random_string(10));
    }
    return data;
}

// Вспомогательная функция для рисования полоски в файл
void write_bar(std::ofstream& out, double val, double max_val, int width = 50) {
    if (max_val == 0) max_val = 1;
    int len = static_cast<int>((val / max_val) * width);
    out << "[";
    for (int i = 0; i < len; ++i) out << "#";
    for (int i = len; i < width; ++i) out << " ";
    out << "] " << std::fixed << std::setprecision(4) << val << "s";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::ofstream result_file("lab5_results.txt");
    if (!result_file.is_open()) {
        std::cerr << "Error: Could not open lab5_results.txt for writing.\n";
        return 1;
    }

    std::vector<size_t> sizes = {10000, 50000, 100000, 500000, 1000000};
    double max_time = 0.0;
    
    struct Result {
        size_t size;
        double splay_time;
        double set_time;
    };
    std::vector<Result> results;

    std::cout << "Running benchmarks (Please wait)...\n";

    // Замеры
    for (size_t n : sizes) {
        std::cout << "Processing N = " << n << "...\n";
        std::vector<std::string> data = generate_data(n);
        
        // 1. Тест Splay Tree
        double splay_dur = 0;
        {
            SplayTree st;
            auto start = std::chrono::high_resolution_clock::now();
            for (const auto& s : data) st.insert(s);
            auto end = std::chrono::high_resolution_clock::now();
            splay_dur = std::chrono::duration<double>(end - start).count();
        }

        // 2. Тест std::set
        double set_dur = 0;
        {
            std::set<std::string> st;
            auto start = std::chrono::high_resolution_clock::now();
            for (const auto& s : data) st.insert(s);
            auto end = std::chrono::high_resolution_clock::now();
            set_dur = std::chrono::duration<double>(end - start).count();
        }

        results.push_back({n, splay_dur, set_dur});
        
        if (splay_dur > max_time) max_time = splay_dur;
        if (set_dur > max_time) max_time = set_dur;
    }

    // Запись графика в файл
    result_file << "=== Performance Graph (Insertion Time vs Data Size) ===\n\n";
    result_file << "Method      | Graph (Visualization)\n";
    result_file << "----------------------------------------------------------------\n";

    for (const auto& res : results) {
        result_file << "\nData Size: " << res.size << "\n";
        
        result_file << "Splay Tree  : ";
        write_bar(result_file, res.splay_time, max_time);
        result_file << "\n";
        
        result_file << "std::set    : ";
        write_bar(result_file, res.set_time, max_time);
        result_file << "\n";
    }
    
    result_file << "\nAnalysis:\n";
    result_file << "std::set (Red-Black Tree) usually performs better on random data inserts\n";
    result_file << "due to lower overhead compared to Splay Tree rotations.\n";

    result_file.close();
    std::cout << "Done! Results saved to 'lab5_results.txt'.\n";

    return 0;
}
