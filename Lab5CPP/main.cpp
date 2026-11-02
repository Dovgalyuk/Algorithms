#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <chrono>
#include "rb_tree.h"

int main(int argc, char* argv[]) {
    RBTree<std::string, std::string> tree;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <input_file.txt>\n";
        return 0;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string k, v;
    while (in >> k >> v) {
        tree.insert(k, v);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto insert_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Loaded " << tree.size() << " elements in " << insert_time << " ms.\n";

    int height = tree.getHeight();
    double max_expected_height = 2.0 * (std::log2(tree.size() + 1));
    std::cout << "Tree height: " << height << " (max expected: " << max_expected_height << ")\n";

    if (height > max_expected_height) {
        std::cerr << "ERROR: Tree is unbalanced after insert (O(N) degradation)!\n";
        return 1;
    }

    in.clear();
    in.seekg(0, std::ios::beg);
    int search_count = 0;
    start = std::chrono::high_resolution_clock::now();
    while (in >> k >> v) {
        if (tree.find(k) != nullptr) {
            search_count++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    auto search_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Found " << search_count << " elements in " << search_time << " ms.\n";

    if (search_count != tree.size()) {
        std::cerr << "ERROR: Some elements were not found!\n";
        return 1;
    }

    in.clear();
    in.seekg(0, std::ios::beg);
    start = std::chrono::high_resolution_clock::now();
    while (in >> k >> v) {
        tree.remove(k);
    }
    end = std::chrono::high_resolution_clock::now();
    auto remove_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Removed elements in " << remove_time << " ms.\n";

    if (tree.size() != 0) {
        std::cerr << "ERROR: Tree is not empty after removing all elements!\n";
        return 1;
    }

    std::cout << "SUCCESS: Stress test passed. No O(N^2) degradation detected.\n";
    return 0;
}