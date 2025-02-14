#include "array.h"

#include <iostream>
#include <ostream>

int main(int argc, char* argv[])
{
    size_t size = 10;
    Array<int>* array = new Array<int>(size);
    std::cout << array->size();
    return 0;
}
