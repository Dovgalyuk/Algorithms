#include <iostream>
#include <string>
#include <sstream>
#include "queue.h"
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>

#define MAX_BITS_IN_STEP 2

constexpr std::size_t powul(std::size_t a, std::size_t pow)
{
    return (pow == 0) ? 1 : a * powul(a, pow - 1);
}

const std::size_t max_number_in_step = powul(2, MAX_BITS_IN_STEP) - 1;

std::vector<std::string> split(std::string input)
{
    std::stringstream ss(input);
    std::vector<std::string> words;
    for (std::string w; ss >> w;)
        words.push_back(w);
    return words;
}

int main()
{
    std::array<Queue<std::size_t>, powul(2, MAX_BITS_IN_STEP)> numbers;

    std::string line;
    std::getline(std::cin, line);

    for (auto c : line)
    {
        if (!(std::isdigit(c) || c == ' '))
        {
            std::cout << "invalid argument" << std::endl;
            return 1;
        }
    }

    std::vector<std::size_t> arr;

    for (auto i : split(line))
        arr.push_back(std::stoull(i));

    // finding max bits.
    std::size_t max_bits = 0;
    for (auto i : arr)
    {
        if (std::pow(2, max_bits) < i)
            max_bits = ceil(std::log2(i));
    }

    std::size_t count_of_steps = ceil(max_bits / (float)MAX_BITS_IN_STEP);

    for (std::size_t step = 0; step < count_of_steps; step++)
    {
        while (!arr.empty())
        {
            numbers[(arr[0] >> (step * MAX_BITS_IN_STEP)) & max_number_in_step].insert(arr[0]);
            arr.erase(arr.begin());
        }
        for (std::size_t i = 0; i < numbers.size(); i++)
        {
            while (!numbers[i].empty())
            {
                arr.push_back(numbers[i].get());
                numbers[i].remove();
            }
        }
    }

    for (auto i : arr)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}
