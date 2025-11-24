#include "../rbtree.h"
#include <iostream>
#include <cassert>

void test_rbtree_basic() {
    RBTree t;
    std::string value;

    t.add("key1", "value1");
    assert(t.get("key1", value) && value == "value1");
    assert(t.count() == 1);

    t.del("key1");
    assert(!t.get("key1", value));
    assert(t.count() == 0);

    std::cout << "RBTree basic tests passed!" << std::endl;
}

int main() {
    test_rbtree_basic();
    return 0;
}