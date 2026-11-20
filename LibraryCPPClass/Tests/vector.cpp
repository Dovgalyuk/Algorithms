#include <iostream>
#include <stdexcept>
#include "vector.h"

int main()
{
    int passed = 0;

    {
        Vector vector;

        vector.resize(5);

        bool correct = vector.size() == 5;

        vector.resize(10);
        correct = correct && vector.size() == 10;

        vector.resize(3);
        correct = correct && vector.size() == 3;

        if (correct)
        {
            passed++;
            std::cout << "[PASSED] Vector resize\n";
        }
        else
        {
            std::cout << "[FAILED] Vector resize\n";
        }
    }

    {
        Vector vector;
        vector.resize(3);

        vector.set(0, 10);
        vector.set(1, 20);
        vector.set(2, 30);

        if (vector.get(0) == 10 &&
            vector.get(1) == 20 &&
            vector.get(2) == 30)
        {
            passed++;
            std::cout << "[PASSED] Vector set and get\n";
        }
        else
        {
            std::cout << "[FAILED] Vector set and get\n";
        }
    }

    {
        Vector vector;
        vector.resize(3);

        vector.set(0, 1);
        vector.set(1, 2);
        vector.set(2, 3);

        Vector copy(vector);
        Vector assigned;
        assigned = vector;

        copy.set(0, 100);
        assigned.set(1, 200);

        if (vector.get(0) == 1 &&
            vector.get(1) == 2 &&
            copy.get(0) == 100 &&
            assigned.get(1) == 200)
        {
            passed++;
            std::cout << "[PASSED] Vector copy and assignment\n";
        }
        else
        {
            std::cout << "[FAILED] Vector copy and assignment\n";
        }
    }

    {
        Vector vector;
        vector.resize(3);

        bool getException = false;
        bool setException = false;

        try
        {
            vector.get(5);
        }
        catch (const std::out_of_range&)
        {
            getException = true;
        }

        try
        {
            vector.set(5, 100);
        }
        catch (const std::out_of_range&)
        {
            setException = true;
        }

        if (getException && setException)
        {
            passed++;
            std::cout << "[PASSED] Vector out of range\n";
        }
        else
        {
            std::cout << "[FAILED] Vector out of range\n";
        }
    }

    std::cout << "\nVector tests: " << passed << "/4\n";

    return passed == 4 ? 0 : 1;
}
