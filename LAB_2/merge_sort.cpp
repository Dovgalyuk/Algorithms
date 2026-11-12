#include "stack.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

typedef std::vector<int> IntVector;

void merge(IntVector &numbers, IntVector &buffer, int left, int right)
{
    int middle = left + (right - left) / 2;
    int i = left;
    int j = middle + 1;
    int k = left;

    while (i <= middle && j <= right)
    {
        if (numbers[i] <= numbers[j]) buffer[k++] = numbers[i++];
        else buffer[k++] = numbers[j++];
    }
    while (i <= middle) buffer[k++] = numbers[i++];
    while (j <= right) buffer[k++] = numbers[j++];
    for (int index = left; index <= right; index++)
    {
        numbers[index] = buffer[index];
    }
}

void mergeSort(IntVector &numbers)
{
    if (numbers.size() < 2) return;
    IntVector buffer(numbers.size());
    Stack tasks;
    tasks.push(0);
    tasks.push(static_cast<int>(numbers.size()) - 1);
    tasks.push(0);

    while (!tasks.empty())
    {
        
        int ready = tasks.get(); tasks.pop();
        int right = tasks.get(); tasks.pop();
        int left = tasks.get(); tasks.pop();
        if (left >= right) continue;

        if (ready == 1)
        {
            merge(numbers, buffer, left, right);
        }
        else
        {
            int middle = left + (right - left) / 2;
            tasks.push(left); tasks.push(right); tasks.push(1);
            tasks.push(middle + 1); tasks.push(right); tasks.push(0);
            tasks.push(left); tasks.push(middle); tasks.push(0);
        }
    }
}

int main(int argc, char *argv[])
{
    const char *filename = DEFAULT_INPUT_FILE;
    if (argc > 1) filename = argv[1];
    std::ifstream input(filename);
    if (!input.is_open())
    {
        std::cerr << "Cannot open input file\n";
        return 1;
    }

    IntVector numbers;
    while (true)
    {
        input >> std::ws;
        if (input.eof()) break;
        int value = 0;
        if (!(input >> value))
        {
            std::cerr << "Expected integer numbers\n";
            return 1;
        }
        if (numbers.size() >= static_cast<size_t>(std::numeric_limits<int>::max()))
        {
            std::cerr << "Too many numbers\n";
            return 1;
        }
        numbers.push_back(value);
    }

    mergeSort(numbers);
    for (size_t i = 0; i < numbers.size(); i++)
    {
        if (i > 0) std::cout << ' ';
        std::cout << numbers[i];
    }
    std::cout << '\n';
    return 0;
}
