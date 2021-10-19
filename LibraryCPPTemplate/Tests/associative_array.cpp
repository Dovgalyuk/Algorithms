#include <iostream>
#include "associative_array.h"

int main() {
    auto* array = new AssociativeArray<int, int>();
    array->insert(5, 1);
    array->insert(4, 1);
    array->insert(3, 1);
    array->insert(1, 1);
    array->insert(2, 1);
    array->write();
    return 0;
}