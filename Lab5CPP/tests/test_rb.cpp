#include <iostream>
#include <cassert>
#include "../rb_tree.h"

int main() {
    RBTree<int, int> tree;

    for (int i = 1; i <= 10; ++i) {
        tree.insert(i, i * 100);
    }
    assert(tree.size() == 10);
    assert(tree.find(5) != nullptr && tree.find(5)->value == 500);
    assert(tree.find(11) == nullptr);

    int expected = 1;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        assert((*it).first == expected);
        expected++;
    }

    tree.remove(5);
    assert(tree.size() == 9);
    assert(tree.find(5) == nullptr);
    tree.remove(1);
    tree.remove(10);
    assert(tree.size() == 7);

    std::cout << "Test passed!\n";
    return 0;
}