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
    if (input.fail() || n != 30)
    {
        std::cerr << "Error. check day count (!= 30).\n";
        return 1;
    }
    Array rainFall(n);
    for (int i = 0; i < n; ++i)
    {
        int value = 0;
        input >> value;
        if (input.fail() || value < 0)
        {
            std::cerr << "Error. check day count\n";
            return 1;
        }
        rainFall.set(i, value);
    }
    long long sum1 = 0;
    long long sum2 = 0;
    long long sum3 = 0;

    for (int i = 0; i < 10; i++)
    {
        sum1 += rainFall.get(i);
    }
    for (int i = 10; i < 20; i++)
    {
        sum2 += rainFall.get(i);
    }
    for (int i = 20; i < 30; i++)
    {
        sum3 += rainFall.get(i);
    }

    std::cout << "First decade: " << sum1 / 10.0 << '\n';
    std::cout << "Second decade: " << sum2 / 10.0 << '\n';
    std::cout << "Third decade: " << sum3 / 10.0 << '\n';
    return 0;
}
