#include <iostream>
#include "DynamicArray.h"

int main() {
    DynamicArray<int> a(3);

    a[0] = 7;
    a[1] = 4;
    a[2] = 9;

    if (a.getSize() != 3)
        return 1;

    if (a[0] != 7 || a[1] != 4 || a[2] != 9)
        return 2;

    DynamicArray<int> b = a;

    if (b.getSize() != 3)
        return 3;

    if (b[0] != 7 || b[1] != 4 || b[2] != 9)
        return 4;

    std::cout << "TEST OK\n";

    return 0;
}
