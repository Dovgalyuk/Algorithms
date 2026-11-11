#include "vector.h"
#include <iostream>

int main()
{
    Vector<int> a;
    if (a.size() != 0) {
        std::cerr << "New vector should be empty\n";
        return 1;
    }

    // Grow repeatedly and check previously written values.
    for (int i = 0; i < 1000; ++i) {
        a.resize(a.size() + 1);
        a.set(i, i * 3);
    }
    for (int i = 0; i < 1000; ++i) {
        if (a.get(i) != i * 3) {
            std::cerr << "Incorrect value at index " << i << '\n';
            return 2;
        }
    }

    // Copy constructor must create an independent copy.
    Vector<int> b(a);
    b.set(0, 12345);
    if (a.get(0) != 0 || b.get(0) != 12345) {
        std::cerr << "Copy constructor failed\n";
        return 3;
    }

    // Assignment operator and self-assignment.
    Vector<int> c;
    c = a;
    c = c;
    if (c.size() != 1000 || c.get(999) != 2997) {
        std::cerr << "Assignment operator failed\n";
        return 4;
    }
    c.set(1, 54321);
    if (a.get(1) != 3) {
        std::cerr << "Assignment must not share storage\n";
        return 5;
    }

    // Shrink, then grow again.
    c.resize(2);
    if (c.size() != 2 || c.get(0) != 0 || c.get(1) != 54321) {
        std::cerr << "Resize down failed\n";
        return 6;
    }
    c.resize(300);
    c.set(299, 777);
    if (c.size() != 300 || c.get(299) != 777) {
        std::cerr << "Resize up failed\n";
        return 7;
    }

    std::cout << "Vector: OK\n";
    return 0;
}
