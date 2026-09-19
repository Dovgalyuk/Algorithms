#include <fstream>
#include <iostream>
#include <string>
#include <array.h>

int main(int argc, char *argv[])
{
    std::string filename = DEFAULT_INPUT_FILE;
    if (argc > 1)
    {
        filename = argv[1];
    }

    std::ifstream input(filename);
    if (!input.is_open())
    {
        std::cerr << "Cannot open input file: " << filename << '\n';
        return 1;
    }
    int n = 0;
    input >> n;
    if (input.fail() || n < 0)
    {
        std::cerr << "Error array size.\n";
        return 1;
    }
    Array arr(n);
    for (int i = 0; i < n; ++i)
    {
        int value = 0;
        input >> value;
        if (input.fail())
        {
            std::cerr << "Cannot read array element.\n";
            return 1;
        }
        arr.set(i, value);
    }
    std::string direction;
    int shift = 0;
    input >> direction >> shift;
    if (input.fail() || shift < 0 ||
        (direction != "left" && direction != "right"))
    {
        std::cerr << "Check shift direction.\n";
        return 1;
    }
    if (shift > n)
    {
        shift = n;
    }
    if (direction == "right")
    {
        for (int i = n - 1; i >= shift; --i)
        {
            arr.set(i, arr.get(i - shift));
        }
        for (int i = 0; i < shift; ++i)
        {
            arr.set(i, 0);
        }
    }
    else
    {
        for (int i = 0; i < n - shift; ++i)
        {
            arr.set(i, arr.get(i + shift));
        }
        for (int i = n - shift; i < n; ++i)
        {
            arr.set(i, 0);
        }
    }
    std::cout << "Result:";
    for (int i = 0; i < n; ++i)
    {
        std::cout << ' ' << arr.get(i);
    }
    std::cout << '\n';
    return 0;
}
