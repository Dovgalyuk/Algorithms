#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "map.h"

using SplayStringMap = SplayMap<std::string, std::string>;
using Order = AssociativeArray<std::string, std::string>::Order;

static void testBasicOperations() {
    SplayStringMap map;
    assert(map.empty());
    assert(map.insert("b", "beta"));
    assert(map.insert("a", "alpha"));
    assert(map.insert("c", "gamma"));
    assert(map.size() == 3);
    assert(!map.insert("a", "new_alpha"));
    assert(*map.find("a") == "new_alpha");
    assert(map.contains("b"));
    assert(!map.contains("z"));

    std::string keys;
    auto it = map.createIterator(Order::Ascending);
    for (; it->valid(); it->next()) keys += it->key();
    assert(keys == "abc");

    assert(map.erase("b"));
    assert(!map.erase("b"));
    assert(map.size() == 2);
    std::cout << "Basic operations passed\n";
}

static void testLoad(size_t count) {
    SplayStringMap map;
    for (size_t i = 0; i < count; ++i) {
        map.insert(std::to_string(i), std::to_string(i));
    }
    assert(map.size() == count);
    for (size_t i = 0; i < count; i += 100) {
        assert(map.find(std::to_string(i)) != nullptr);
    }
    map.clear();
    assert(map.empty());
    std::cout << "Load test passed for size: " << count << "\n";
}

int main() {
    testBasicOperations();
    testLoad(1000000);
    std::cout << "All tests passed!\n";
    return 0;
}