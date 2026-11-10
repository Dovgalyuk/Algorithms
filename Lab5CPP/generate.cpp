#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 4)
            throw runtime_error("Usage: Lab5CPPGenerate output.txt count ascending|descending|random");

        string argument = argv[2];
        if (argument.empty() || argument.find_first_not_of("0123456789") != string::npos)
            throw runtime_error("Invalid count");
        unsigned long long number = stoull(argument);
        if (number == 0 || number > numeric_limits<size_t>::max())
            throw runtime_error("Invalid count");
        size_t count = static_cast<size_t>(number);

        string order = argv[3];
        if (order != "ascending" && order != "descending" && order != "random")
            throw runtime_error("Invalid order");

        vector<size_t> numbers(count);
        iota(numbers.begin(), numbers.end(), size_t{0});
        if (order == "descending")
            reverse(numbers.begin(), numbers.end());
        if (order == "random")
        {
            mt19937 generator(5093);
            shuffle(numbers.begin(), numbers.end(), generator);
        }

        ofstream output(argv[1]);
        if (!output)
            throw runtime_error("Cannot open output file");
        int width = static_cast<int>(max(size_t{10}, to_string(count - 1).size()));
        output << setfill('0');
        for (size_t value : numbers)
            output << "key" << setw(width) << value << '\n';
        output.close();
        if (!output)
            throw runtime_error("Cannot write output file");

        cout << count << '\n';
        return 0;
    }
    catch (const exception &error)
    {
        cerr << error.what() << '\n';
        return 1;
    }
}
