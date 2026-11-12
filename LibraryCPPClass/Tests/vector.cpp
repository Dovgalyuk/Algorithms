#include <stdexcept>
#include <iostream>
#include "vector.h"

bool checkVector()
{
    Vector a;
    if (a.size() != 0) return false;
    a.resize(4);
    for (size_t i = 0; i < 4; i++)
    {
        if (a.get(i) != 0) return false;
        a.set(i, static_cast<int>(i + 10));
    }
    a.resize(2);
    a.resize(5);
    if (a.get(0) != 10 || a.get(1) != 11 || a.get(2) != 0) return false;
    Vector copy(a);
    Vector assigned;
    assigned.resize(1);
    assigned = a;
    a.set(0, -1);
    if (copy.get(0) != 10 || assigned.get(0) != 10) return false;
    try { a.get(a.size()); return false; }
    catch (const std::out_of_range &) {}
    try { a.set(a.size(), 1); return false; }
    catch (const std::out_of_range &) {}
    a.resize(0);
    assigned = a;
    if (assigned.size() != 0) return false;
    a.resize(3);
    return a.get(0) == 0 && a.get(2) == 0;
}
int main()
{
    if (!checkVector()) return 1;
    Vector vector;

    vector.resize(5);
    if (vector.size() != 5)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector.size() ; ++i)
        vector.set(i, static_cast<int>(i));

    vector = vector;

    for (size_t i = 0 ; i < vector.size() ; ++i)
    {
        if (vector.get(i) != (Data)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    vector.resize(10);
    if (vector.size() != 10)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector.size() ; ++i)
        std::cout << vector.get(i) << " ";
    std::cout << "\n";

    vector.resize(3);
    if (vector.size() != 3)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector.size() ; ++i)
    {
        if (vector.get(i) != (Data)i)
        {
            std::cout << "Invalid vector element " << i << "\n";
            return 1;
        }
    }

    std::cout << "Vector: ";
    for (size_t i = 0 ; i < vector.size() ; ++i)
        std::cout << vector.get(i) << " ";
    std::cout << "\n";

    // Performance test
    for (int i = 1 ; i <= 10000000 ; ++i)
    {
        vector.resize(i);
        vector.set(i - 1, i);
    }

    Vector copy = vector;

    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i)
        sum += vector.get(i);

    std::cout << sum << "\n";
}
