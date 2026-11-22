#include <cassert>
#include <iostream>
#include <string>

#include "list.h"

using graph::List;

static void testEmpty() {
    List<int> l;
    assert(l.size() == 0);
    assert(l.empty());
    assert(l.begin() == l.end());
    std::cout << "[OK] testEmpty\n";
}

static void testPushBack() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    assert(l.size() == 3);
    assert(!l.empty());
    assert(l.valueAt(0) == 1);
    assert(l.valueAt(1) == 2);
    assert(l.valueAt(2) == 3);
    std::cout << "[OK] testPushBack\n";
}

static void testIterate() {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    int sum = 0;
    int count = 0;
    for (List<int>::iterator it = l.begin(); it != l.end(); ++it) {
        sum += *it;
        ++count;
    }
    assert(count == 3);
    assert(sum == 60);
    std::cout << "[OK] testIterate\n";
}

static void testConstIterate() {
    List<int> l;
    l.push_back(5);
    l.push_back(6);
    const List<int>& cl = l;
    int sum = 0;
    for (List<int>::const_iterator it = cl.begin(); it != cl.end(); ++it) {
        sum += *it;
    }
    assert(sum == 11);
    std::cout << "[OK] testConstIterate\n";
}

static void testCopyCtor() {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int> b(a);
    assert(b.size() == 3);
    assert(b.valueAt(0) == 1);
    assert(b.valueAt(1) == 2);
    assert(b.valueAt(2) == 3);
    b.push_back(4);
    assert(a.size() == 3);
    assert(b.size() == 4);
    std::cout << "[OK] testCopyCtor\n";
}

static void testAssign() {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    List<int> b;
    b.push_back(9);
    b.push_back(8);
    b.push_back(7);
    b = a;
    assert(b.size() == 2);
    assert(b.valueAt(0) == 1);
    assert(b.valueAt(1) == 2);
    std::cout << "[OK] testAssign\n";
}

static void testErase() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    List<int>::iterator it = l.begin();
    ++it;
    it = l.erase(it);
    assert(l.size() == 3);
    assert(l.valueAt(0) == 1);
    assert(l.valueAt(1) == 3);
    assert(l.valueAt(2) == 4);
    assert(*it == 3);
    l.erase(l.begin());
    assert(l.size() == 2);
    assert(l.valueAt(0) == 3);
    assert(l.valueAt(1) == 4);
    std::cout << "[OK] testErase\n";
}

static void testEraseEnd() {
    List<int> l;
    l.push_back(1);
    List<int>::iterator it = l.erase(l.end());
    assert(it == l.end());
    assert(l.size() == 1);
    (void)it;
    std::cout << "[OK] testEraseEnd\n";
}

static void testClear() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.clear();
    assert(l.size() == 0);
    assert(l.empty());
    assert(l.begin() == l.end());
    l.push_back(42);
    assert(l.size() == 1);
    assert(l.valueAt(0) == 42);
    std::cout << "[OK] testClear\n";
}

static void testValueAtMutable() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.valueAt(0) = 100;
    l.valueAt(1) = 200;
    assert(l.valueAt(0) == 100);
    assert(l.valueAt(1) == 200);
    std::cout << "[OK] testValueAtMutable\n";
}

static void testStrings() {
    List<std::string> l;
    l.push_back("alpha");
    l.push_back("beta");
    l.push_back("gamma");
    assert(l.size() == 3);
    assert(l.valueAt(0) == "alpha");
    assert(l.valueAt(1) == "beta");
    assert(l.valueAt(2) == "gamma");
    std::cout << "[OK] testStrings\n";
}

static void testArrow() {
    List<std::string> l;
    l.push_back("hello");
    List<std::string>::iterator it = l.begin();
    assert(it->size() == 5);
    assert(*it == "hello");
    (void)it;
    std::cout << "[OK] testArrow\n";
}

int main() {
    testEmpty();
    testPushBack();
    testIterate();
    testConstIterate();
    testCopyCtor();
    testAssign();
    testErase();
    testEraseEnd();
    testClear();
    testValueAtMutable();
    testStrings();
    testArrow();
    std::cout << "All list tests passed.\n";
    return 0;
}
