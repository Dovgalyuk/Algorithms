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

void test_rbtree_1000_elements() {
    RBTree t;
    std::string value;

    for (int i = 0; i < 1000; i++) {
        t.add("key" + std::to_string(i), "value" + std::to_string(i));
    }
    assert(t.count() == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(t.get("key" + std::to_string(i), value));
        assert(value == "value" + std::to_string(i));
    }

    for (int i = 0; i < 1000; i++) {
        t.del("key" + std::to_string(i));
    }
    assert(t.count() == 0);

    std::cout << "1,000 elements test passed!" << std::endl;
}

void test_rbtree_10000_elements() {
    RBTree t;
    std::string value;

    for (int i = 0; i < 10000; i++) {
        t.add("k" + std::to_string(i), "v" + std::to_string(i));
    }
    assert(t.count() == 10000);

    for (int i = 0; i < 10000; i += 10) {
        assert(t.get("k" + std::to_string(i), value));
        assert(value == "v" + std::to_string(i));
    }

    for (int i = 0; i < 10000; i++) {
        t.del("k" + std::to_string(i));
    }
    assert(t.count() == 0);

    std::cout << "10,000 elements test passed!" << std::endl;
}

void test_rbtree_100000_elements() {
    RBTree t;
    std::string value;

    for (int i = 0; i < 100000; i++) {
        t.add("key_" + std::to_string(i), "val_" + std::to_string(i));
    }
    assert(t.count() == 100000);

    for (int i = 0; i < 100000; i += 100) {
        assert(t.get("key_" + std::to_string(i), value));
        assert(value == "val_" + std::to_string(i));
    }

    for (int i = 0; i < 100000; i++) {
        t.del("key_" + std::to_string(i));
    }
    assert(t.count() == 0);

    std::cout << "100,000 elements test passed!" << std::endl;
}

void test_rbtree_1_million() {
    RBTree t;

    for (int i = 0; i < 1000000; i++) {
        t.add("m" + std::to_string(i), "value" + std::to_string(i));
    }
    assert(t.count() == 1000000);

    for (int i = 0; i < 1000000; i++) {
        t.del("m" + std::to_string(i));
    }
    assert(t.count() == 0);

    std::cout << "1,000,000 elements test passed!" << std::endl;
}

int main() {
    test_rbtree_basic();
    test_rbtree_1000_elements();   
    test_rbtree_10000_elements();    
    test_rbtree_100000_elements();
    test_rbtree_1_million();       

    std::cout << "ALL TESTS PASSED!" << std::endl;
    return 0;
}