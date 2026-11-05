#include <iostream>
#include <stdexcept>
#include <string>
#include "vector.h"

using namespace std;

typedef Vector<int> MyVector;


typedef Vector<string> StringVector;

void check(bool condition, const char *message)
{
    if (!condition)
        throw runtime_error(message);
}

void test_vector()
{
    StringVector values;
    values.resize(3);
    check(values[0].empty() && values[2].empty(), "Vector defaults");
    values[0] = "one";
    values[1] = "two";
    values[2] = "three";
    values.resize(1);
    values.resize(3);
    check(values[0] == "one" && values[1].empty() && values[2].empty(), "Vector regrow");
    values.resize(100);
    check(values[0] == "one" && values[99].empty(), "Vector expansion");
    StringVector copy(values);
    copy[0] = "changed";
    check(values[0] == "one", "Vector independent copy");
    copy = values;
    copy = copy;
    check(copy[0] == "one" && copy.size() == 100, "Vector assignment");
    copy.resize(0);
    copy.resize(1);
    check(copy[0].empty(), "Vector reuse");
    copy = StringVector();
    check(copy.size() == 0, "Assign empty vector");
}

int main()
{
    try
    {
        test_vector();
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }

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
