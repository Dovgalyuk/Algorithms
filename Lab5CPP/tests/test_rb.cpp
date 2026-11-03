#include <iostream>
#include <chrono>
#include "../rb_tree.h"

bool check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << "\n";
        return false;
    }
    return true;
}

int main() {
    RBTree<int, int> tree;

    for (int i = 1; i <= 10; ++i) {
        tree.insert(i, i * 100);
    }
    if (!check(tree.size() == 10, "Size should be 10")) return 1;
    if (!check(tree.find(5) != nullptr && tree.find(5)->value == 500, "Find failed")) return 1;
    if (!check(tree.find(11) == nullptr, "Found non-existent element")) return 1;

    int expected = 1;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        if (!check((*it).first == expected, "Iterator order failed")) return 1;
        expected++;
    }

    tree.remove(5);
    if (!check(tree.size() == 9, "Size after remove should be 9")) return 1;
    tree.remove(1);
    tree.remove(10);
    if (!check(tree.size() == 7, "Size after more removes should be 7")) return 1;

    const int N = 100000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        tree.insert(i + 1000, i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Inserted " << N << " elements in " << time_ms << " ms.\n";

    if (!check(time_ms < 1000, "Performance test failed (took too long, O(N^2) degradation?)")) return 1;

    std::cout << "Test passed!\n";
    return 0;
}
