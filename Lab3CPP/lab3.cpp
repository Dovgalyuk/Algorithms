#include <iostream>
#include <string>
#include <sstream>
#include "queue.h"
#include <cmath>
#include <array>
#include <vector>
#include <algorithm>

constexpr std::size_t powl(std::size_t a, std::size_t pow)
{
    return (pow == 0) ? 1 : a * powl(a, pow - 1);
}

const std::size_t count_of_bits_in_step = 2;
const std::size_t max_number_in_step = powl(2, count_of_bits_in_step) - 1;

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
    std::array<Queue<std::size_t>, powl(2, count_of_bits_in_step)> numbers;

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

    std::size_t count_of_steps = ceil(max_bits / (float)count_of_bits_in_step);

    for (std::size_t step = 0; step < count_of_steps; step++)
    {
        while (!arr.empty())
        {
            numbers[(arr[0] >> (step * count_of_bits_in_step)) & max_number_in_step].insert(arr[0]);
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
