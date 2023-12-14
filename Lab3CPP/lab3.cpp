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
    std::size_t result = 1;
    for (std::size_t i = 0; i < pow; i++)
        result *= a;
    return result;
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

void digit_sort(std::vector<std::size_t> &arr)
{
    std::array<Queue<std::size_t>, powul(2, MAX_BITS_IN_STEP)> numbers;

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
        for (std::size_t i = 0; i < arr.size(); i++)
            numbers[(arr[i] >> (step * MAX_BITS_IN_STEP)) & max_number_in_step].insert(arr[i]);
        arr.clear();
        for (std::size_t i = 0; i < numbers.size(); i++)
        {
            while (!numbers[i].empty())
            {
                arr.push_back(numbers[i].get());
                numbers[i].remove();
            }
        }
    }
}

int main()
{
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

    digit_sort(arr);

    for (auto i : arr)
        std::cout << i << ' ';
    std::cout << std::endl;

    return 0;
}