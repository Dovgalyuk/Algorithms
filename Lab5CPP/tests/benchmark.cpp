#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <map>
#include <unordered_map>
#include "../rb_tree.h"

void writeCSVHeader(std::ofstream& out) {
    out << "N;RBTree_Time;Map_Time;UnorderedMap_Time\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_csv>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) return 1;

    std::ofstream out(argv[2]);
    if (!out.is_open()) return 1;
    writeCSVHeader(out);

    std::vector<std::pair<std::string, std::string>> data;
    std::string k, v;
    while (in >> k >> v) {
        data.push_back({ k, v });
    }
    in.close();

    std::cout << "Loaded " << data.size() << " items. Starting tests...\n";

    std::vector<int> test_sizes = { 10000, 50000, 100000, 500000, 1000000 };

    for (int n : test_sizes) {
        if (n > (int)data.size()) break;

        std::cout << "Testing N = " << n << "...\n";

        auto start = std::chrono::high_resolution_clock::now();
        RBTree<std::string, std::string> rb_tree;
        for (int i = 0; i < n; ++i) {
            rb_tree.insert(data[i].first, data[i].second);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto rb_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        std::map<std::string, std::string> std_map;
        for (int i = 0; i < n; ++i) {
            std_map[data[i].first] = data[i].second;
        }
        end = std::chrono::high_resolution_clock::now();
        auto map_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        std::unordered_map<std::string, std::string> std_unordered_map;
        for (int i = 0; i < n; ++i) {
            std_unordered_map[data[i].first] = data[i].second;
        }
        end = std::chrono::high_resolution_clock::now();
        auto umap_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        out << n << ";" << rb_time << ";" << map_time << ";" << umap_time << "\n";
    }

    out.close();
    std::cout << "Benchmarks saved to " << argv[2] << "\n";
    return 0;
}