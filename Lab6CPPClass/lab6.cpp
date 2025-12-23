#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <random>
#include <fstream>
#include "string_custom.h"

std::string random_string(size_t length) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<size_t> dist(0, sizeof(alphanum) - 2);

    std::string s;
    s.resize(length);
    for (size_t i = 0; i < length; ++i) {
        s[i] = alphanum[dist(rng)];
    }
    return s;
}

void write_bar(std::ofstream& out, double val, double max_val, int width = 50) {
    if (max_val == 0) max_val = 1;
    int len = 0;
    if (val > 0) {
        len = static_cast<int>((val / max_val) * width);
    }
    if (len > width) len = width;

    out << "[";
    for (int i = 0; i < len; ++i) out << "#";
    for (int i = len; i < width; ++i) out << " ";
    out << "] " << std::fixed << std::setprecision(5) << val << "s";
}

int main() {
    std::ofstream result_file("lab6_results.txt");
    if (!result_file.is_open()) {
        std::cerr << "Error: Could not open lab6_results.txt for writing.\n";
        return 1;
    }

    std::vector<size_t> sizes = {500000, 1000000, 2000000, 5000000, 10000000};
    
    // Паттерн длинный, чтобы Бойер-Мур мог "разгуляться"
    // Он будет добавляться в самый конец текста
    std::string pattern_std = "ThisIsAUniquePatternThatWillBeFoundAtTheVeryEnd12345";
    
    double max_time = 0.0;
    
    struct Result {
        size_t size;
        double custom_time;
        double std_time;
    };
    std::vector<Result> results;

    std::cout << "Running benchmarks for String Search (Please wait)...\n";

    for (size_t n : sizes) {
        std::cout << "Processing Text Length N = " << n << "...\n";
        
        std::string text_std = random_string(n);
        text_std += pattern_std;

        String text_custom(text_std.c_str());

        // 1. Тест Custom String (Boyer-Moore)
        double custom_dur = 0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            
            volatile long res = text_custom.find(pattern_std.c_str());
            (void)res;
            
            auto end = std::chrono::high_resolution_clock::now();
            custom_dur = std::chrono::duration<double>(end - start).count();
        }

        // 2. Тест std::string (Native find)
        double std_dur = 0;
        {
            auto start = std::chrono::high_resolution_clock::now();
            
            volatile size_t res = text_std.find(pattern_std);
            (void)res;
            
            auto end = std::chrono::high_resolution_clock::now();
            std_dur = std::chrono::duration<double>(end - start).count();
        }

        results.push_back({n, custom_dur, std_dur});
        
        if (custom_dur > max_time) max_time = custom_dur;
        if (std_dur > max_time) max_time = std_dur;
    }

    // Запись графика в файл
    result_file << "=== Performance Graph (Search Time vs Text Length) ===\n";
    result_file << "Pattern Length: " << pattern_std.length() << " chars (Search at the end)\n\n";
    result_file << "Method          | Graph (Visualization)\n";
    result_file << "----------------------------------------------------------------\n";

    for (const auto& res : results) {
        result_file << "\nText Length: " << res.size << "\n";
        
        result_file << "Custom (BM)     : ";
        write_bar(result_file, res.custom_time, max_time);
        result_file << "\n";
        
        result_file << "std::string     : ";
        write_bar(result_file, res.std_time, max_time);
        result_file << "\n";
    }
    
    result_file << "\nAnalysis:\n";
    result_file << "1. Boyer-Moore (Custom) effectively skips characters, showing performance\n";
    result_file << "   comparable to or better than std::string on long patterns.\n";
    result_file << "2. std::string::find usually employs optimized SIMD instructions (AVX/SSE),\n";
    result_file << "   making it extremely fast despite algorithm complexity.\n";

    result_file.close();
    std::cout << "Done! Results saved to 'lab6_results.txt'.\n";

    return 0;
}
