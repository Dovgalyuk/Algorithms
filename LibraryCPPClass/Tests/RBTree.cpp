#include "RBTree.h"
#include <iostream>
#include <string>

using namespace std;

void check(bool condition, const string& message) {
    if (condition == false) {
        cout << "Test failed: " << message << endl;
        exit(1);
    }
}

void test_basic() {
    RBTree t;
    string value;

    t.insert("key1", "value1");
    check(t.find("key1", value), "find key1");
    check(value == "value1", "value1 correct");
    check(t.size() == 1, "size after insert");

    t.remove("key1");
    check(!t.find("key1", value), "key1 removed");
    check(t.size() == 0, "size after remove");

    cout << "Basic tests passed" << endl;
}

void test_1000() {
    RBTree t;
    string value;

    for (int i = 0; i < 1000; i++) {
        t.insert("key" + to_string(i), "value" + to_string(i));
    }
    check(t.size() == 1000, "size 1000");

    for (int i = 0; i < 1000; i++) {
        check(t.find("key" + to_string(i), value), "find key" + to_string(i));
        check(value == "value" + to_string(i), "value" + to_string(i) + " correct");
    }

    for (int i = 0; i < 1000; i++) {
        t.remove("key" + to_string(i));
    }
    check(t.size() == 0, "empty after remove all");

    cout << "1000 elements test passed" << endl;
}

void test_10000() {
    RBTree t;
    string value;

    for (int i = 0; i < 10000; i++) {
        t.insert("k" + to_string(i), "v" + to_string(i));
    }
    check(t.size() == 10000, "size 10000");

    for (int i = 0; i < 10000; i = i + 100) {
        check(t.find("k" + to_string(i), value), "find k" + to_string(i));
        check(value == "v" + to_string(i), "v" + to_string(i) + " correct");
    }

    for (int i = 0; i < 10000; i++) {
        t.remove("k" + to_string(i));
    }
    check(t.size() == 0, "empty after remove 10000");

    cout << "10000 elements test passed" << endl;
}

void test_updates() {
    RBTree t;
    string value;

    t.insert("key", "value1");
    t.insert("key", "value2");

    check(t.find("key", value), "find after update");
    check(value == "value2", "updated value correct");
    check(t.size() == 1, "size stays 1 after update");

    cout << "Update test passed" << endl;
}

void test_mixed() {
    RBTree t;
    string value;

    for (int i = 0; i < 500; i++) {
        t.insert("mixed" + to_string(i), "data" + to_string(i));
    }

    for (int i = 0; i < 500; i = i + 2) {
        t.remove("mixed" + to_string(i));
    }

    for (int i = 1; i < 500; i = i + 2) {
        check(t.find("mixed" + to_string(i), value), "find mixed" + to_string(i));
    }

    for (int i = 0; i < 500; i = i + 2) {
        check(!t.find("mixed" + to_string(i), value), "mixed" + to_string(i) + " removed");
    }

    check(t.size() == 250, "size after mixed operations");

    cout << "Mixed operations test passed" << endl;
}

int main() {
    cout << "Starting RBTree tests..." << endl;

    test_basic();
    test_updates();
    test_1000();
    test_10000();
    test_mixed();

    cout << "\nAll tests passed!" << endl;
    return 0;
}