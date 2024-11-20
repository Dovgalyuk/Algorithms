#include <iostream>
#include "vector.h"

int main()
{
    Vector vector;

    vector.resize(5);
    if (vector.size() != 5)
    {
        std::cout << "Invalid resize\n";
        return 1;
    }

    for (size_t i = 0 ; i < vector.size() ; ++i)
        vector.set(i, i);

    for (size_t i = 0 ; i < vector.size() ; ++i)
    {
        if (vector.get(i) != (int)i)
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
        if (vector.get(i) != (int)i)
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

    Vector vector_copy(vector);
    for (size_t i = 0; i < vector_copy.size(); ++i)
    {
        if (vector_copy.get(i) != vector.get(i))
        {
            std::cout << "Copy constructor failed at element " << i << "\n";
            return 1;
        }
    }

    Vector assigned_vector;
    assigned_vector = vector;
    for (size_t i = 0; i < assigned_vector.size(); ++i)
    {
        if (assigned_vector.get(i) != vector.get(i))
        {
            std::cout << "Assignment operator failed at element " << i << "\n";
            return 1;
        }
    }

    try
    {
        vector.get(vector.size());
        std::cout << "Failed to catch out-of-bounds access\n";
        return 1;
    }
    catch (const std::out_of_range &)
    {
        std::cout << "Caught out-of-bounds access\n";
    }

}