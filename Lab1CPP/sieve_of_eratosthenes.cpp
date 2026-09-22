#include <iostream>
#include <fstream>

#include "array.h"

Array<int> create_sieve(size_t size)
{
    Array<int> array(size);

    for (size_t i = 0; i < size; ++i)
    {
        array.set(i, (int)i + 1);
    }

    if (size > 0)
    {
        array.set(0, 0);
    }

    for (size_t p = 2; p <= size / p; ++p)
    {
        if (array.get(p - 1) != 0)
        {
            for (size_t k = p * p; k <= size; k += p)
                array.set(k - 1, 0);
        }
    }

    return array;
}

void move_to_front(Array<int>& array)
{
    size_t count = 0;

    for (size_t i = 0; i < array.size(); ++i)
    {
        int value = array.get(i);
        if (value != 0)
        {
            array.set(count, value);
            ++count;
        }
    }

    for (size_t i = count; i < array.size(); ++i)
    {
        array.set(i, 0);
    }
}

void print_array(const Array<int>& array) {
    for (size_t i = 0; i < array.size(); ++i)
    {
        std::cout << array.get(i) << ' ';
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    if (argc <= 1)
    {
        std::cerr << "Missing command-line arguments" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);

    size_t size;
    if (!(fin >> size))
    {
        std::cerr << "Cannot read array size" << std::endl;
        return 1;
    };

    Array<int> array = create_sieve(size);
    move_to_front(array);
    print_array(array);

    return 0;
}