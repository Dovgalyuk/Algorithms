#include <cstdlib>
#include <iostream>
#include <string>

#include "list.h"

using graph::List;

static void check(bool cond, const char* expr, const char* file, int line) {
    if (!cond) {
        std::cerr << "CHECK failed: " << expr << " at " << file << ":" << line << "\n";
        std::exit(1);
    }
}

static void testEmpty() {
    List<int> l;
    check(l.size() == 0, "l.size() == 0", __FILE__, __LINE__);
    check(l.empty(), "l.empty()", __FILE__, __LINE__);
    check(l.begin() == l.end(), "l.begin() == l.end()", __FILE__, __LINE__);
    std::cout << "[OK] testEmpty\n";
}

static void testPushBack() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    check(l.size() == 3, "l.size() == 3", __FILE__, __LINE__);
    check(!l.empty(), "!l.empty()", __FILE__, __LINE__);
    int expected[] = {1, 2, 3};
    int i = 0;
    for (List<int>::iterator it = l.begin(); it != l.end(); ++it) {
        check(*it == expected[i], "*it == expected[i]", __FILE__, __LINE__);
        ++i;
    }
    check(i == 3, "i == 3", __FILE__, __LINE__);
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
    check(count == 3, "count == 3", __FILE__, __LINE__);
    check(sum == 60, "sum == 60", __FILE__, __LINE__);
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
    check(sum == 11, "sum == 11", __FILE__, __LINE__);
    std::cout << "[OK] testConstIterate\n";
}

static void testCopyCtor() {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    List<int> b(a);
    check(b.size() == 3, "b.size() == 3", __FILE__, __LINE__);
    int expected[] = {1, 2, 3};
    int i = 0;
    for (List<int>::iterator it = b.begin(); it != b.end(); ++it) {
        check(*it == expected[i], "*it == expected[i]", __FILE__, __LINE__);
        ++i;
    }
    b.push_back(4);
    check(a.size() == 3, "a.size() == 3", __FILE__, __LINE__);
    check(b.size() == 4, "b.size() == 4", __FILE__, __LINE__);
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
    check(b.size() == 2, "b.size() == 2", __FILE__, __LINE__);
    int expected[] = {1, 2};
    int i = 0;
    for (List<int>::iterator it = b.begin(); it != b.end(); ++it) {
        check(*it == expected[i], "*it == expected[i]", __FILE__, __LINE__);
        ++i;
    }
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
    check(l.size() == 3, "l.size() == 3", __FILE__, __LINE__);
    check(*it == 3, "*it == 3", __FILE__, __LINE__);
    int expected[] = {1, 3, 4};
    int i = 0;
    for (List<int>::iterator jt = l.begin(); jt != l.end(); ++jt) {
        check(*jt == expected[i], "*jt == expected[i]", __FILE__, __LINE__);
        ++i;
    }
    l.erase(l.begin());
    check(l.size() == 2, "l.size() == 2", __FILE__, __LINE__);
    int expected2[] = {3, 4};
    i = 0;
    for (List<int>::iterator jt = l.begin(); jt != l.end(); ++jt) {
        check(*jt == expected2[i], "*jt == expected2[i]", __FILE__, __LINE__);
        ++i;
    }
    std::cout << "[OK] testErase\n";
}

static void testEraseEnd() {
    List<int> l;
    l.push_back(1);
    List<int>::iterator it = l.erase(l.end());
    check(it == l.end(), "it == l.end()", __FILE__, __LINE__);
    check(l.size() == 1, "l.size() == 1", __FILE__, __LINE__);
    std::cout << "[OK] testEraseEnd\n";
}

static void testClear() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.clear();
    check(l.size() == 0, "l.size() == 0", __FILE__, __LINE__);
    check(l.empty(), "l.empty()", __FILE__, __LINE__);
    check(l.begin() == l.end(), "l.begin() == l.end()", __FILE__, __LINE__);
    l.push_back(42);
    check(l.size() == 1, "l.size() == 1", __FILE__, __LINE__);
    check(*l.begin() == 42, "*l.begin() == 42", __FILE__, __LINE__);
    std::cout << "[OK] testClear\n";
}

static void testStrings() {
    List<std::string> l;
    l.push_back("alpha");
    l.push_back("beta");
    l.push_back("gamma");
    check(l.size() == 3, "l.size() == 3", __FILE__, __LINE__);
    const char* expected[] = {"alpha", "beta", "gamma"};
    int i = 0;
    for (List<std::string>::iterator it = l.begin(); it != l.end(); ++it) {
        check(*it == expected[i], "*it == expected[i]", __FILE__, __LINE__);
        ++i;
    }
    std::cout << "[OK] testStrings\n";
}

static void testArrow() {
    List<std::string> l;
    l.push_back("hello");
    List<std::string>::iterator it = l.begin();
    check(it->size() == 5, "it->size() == 5", __FILE__, __LINE__);
    check(*it == "hello", "*it == hello", __FILE__, __LINE__);
    std::cout << "[OK] testArrow\n";
}

static void testMutableThroughIterator() {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    for (List<int>::iterator it = l.begin(); it != l.end(); ++it) {
        *it *= 10;
    }
    int expected[] = {10, 20};
    int i = 0;
    for (List<int>::iterator it = l.begin(); it != l.end(); ++it) {
        check(*it == expected[i], "*it == expected[i]", __FILE__, __LINE__);
        ++i;
    }
    std::cout << "[OK] testMutableThroughIterator\n";
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
    testStrings();
    testArrow();
    testMutableThroughIterator();
    std::cout << "All list tests passed.\n";
    return 0;
}
