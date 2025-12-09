#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "splay_tree.h"

// Проверка базовой логики: добавление, поиск, удаление
void test_correctness() {
    SplayTree st;
    
    // 1. Вставка
    st.insert("apple");
    st.insert("banana");
    st.insert("cherry");

    // 2. Поиск
    if (st.contains("apple") && st.contains("banana") && st.contains("cherry")) {
        std::cout << "[OK] Insert and Find existing elements passed.\n";
    } else {
        std::cerr << "[FAIL] Insert or Find broken.\n";
        exit(1);
    }

    if (!st.contains("dragonfruit")) {
        std::cout << "[OK] Find non-existing element passed.\n";
    } else {
        std::cerr << "[FAIL] Found element that shouldn't exist.\n";
        exit(1);
    }

    // 3. Удаление
    st.remove("banana");
    if (!st.contains("banana") && st.contains("apple")) {
        std::cout << "[OK] Remove passed.\n";
    } else {
        std::cerr << "[FAIL] Remove broken.\n";
        exit(1);
    }
}

// Нагрузочное тестирование
void test_performance_sorted() {
    SplayTree st;
    const int N = 1000000;
    
    std::vector<std::string> data;
    data.reserve(N);
    for (int i = 0; i < N; ++i) {
        data.push_back(std::to_string(i));
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    for (const auto& s : data) {
        st.insert(s);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "[INFO] Sorted insert of " << N << " elements took " << diff.count() << "s.\n";

    if (diff.count() > 1.0) {
        std::cerr << "[FAIL] Performance test failed! Possible O(N^2) complexity detected.\n";
        exit(1);
    } else {
        std::cout << "[OK] Performance test passed (Linear complexity confirmed).\n";
    }
}

int main() {
    test_correctness();
    test_performance_sorted();
    return 0;
}