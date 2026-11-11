#include <iostream>
#include "vector.h"

typedef Vector<int> MyVector;

int main()
{
    MyVector vector;

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

    MyVector assigned;
    assigned = vector;
    vector.set(0, 100);

    if (assigned.get(0) != 0)
    {
        std::cout << "Invalid assignment copy\n";
        return 1;
    }

    vector.set(0, 0);

    MyVector populated;
    populated.resize(10);
    populated = vector;
    vector.set(1, 100);
    if (populated.size() != 3 || populated.get(0) != 0 ||
        populated.get(1) != 1 || populated.get(2) != 2)
    {
        std::cout << "Invalid assignment to populated vector\n";
        return 1;
    }
    vector.set(1, 1);

    MyVector empty;
    MyVector emptyCopy(empty);
    populated = empty;
    empty = empty;
    if (populated.size() != 0 || emptyCopy.size() != 0 || empty.size() != 0)
    {
        std::cout << "Invalid empty vector copy\n";
        return 1;
    }

    populated = vector;
    populated.resize(5);
    if (populated.size() != 5 || populated.get(0) != 0 ||
        populated.get(1) != 1 || populated.get(2) != 2 ||
        populated.get(3) != 0 || populated.get(4) != 0)
    {
        std::cout << "Invalid resize after assignment\n";
        return 1;
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

    MyVector copy = vector;

    for (int i = 0 ; i < 10000000 ; ++i)
    {
        if (vector.get(i) != copy.get(i))
        {
            std::cout << "Invalid copy element " << i << "\n";
            return 1;
        }
    }

    long long sum = 0;
    for (int i = 0 ; i < 10000000 ; ++i)
        sum += vector.get(i);

    std::cout << sum << "\n";
}
