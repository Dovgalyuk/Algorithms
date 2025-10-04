#include <iostream>
#include <fstream>
#include <vector>
#include "array.h"

Array* array_create_and_read(std::istream& input)
{
    size_t n;
    input >> n;

    /* Create array */
    Array* arr = array_create(n);
    /* Read array data */
    for (size_t i = 0; i < n; ++i)
    {
        Data x;
        input >> x;
        array_set(arr, i, x);
    }
    return arr;
}

Array* array_create_read_size(std::istream& input)
{
    size_t n;
    input >> n;
    return array_create(n);
}

/* Read an integer from a file, create an array of this size and fill it with numbers from the file.
   Find the number of elements whose value is greater than the arithmetic mean of the minimum
   and maximum elements of the array, and print their numbers. Display the result on the screen. */
void task1(Array* arr)
{
    size_t n = array_size(arr);
    if (n == 0) {
        std::cout << "Array is empty" << std::endl;
        return;
    }

    // Find min and max elements
    Data min_val = array_get(arr, 0);
    Data max_val = array_get(arr, 0);

    for (size_t i = 1; i < n; ++i) {
        Data current = array_get(arr, i);
        if (current < min_val) min_val = current;
        if (current > max_val) max_val = current;
    }

    // Calculate average of min and max
    double average = (static_cast<double>(min_val) + max_val) / 2.0;

    // Find elements greater than average and their indices
    std::vector<size_t> indices;
    for (size_t i = 0; i < n; ++i) {
        if (array_get(arr, i) > average) {
            indices.push_back(i);
        }
    }

    // Display results
    std::cout << "Array: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << "\nMin: " << min_val << ", Max: " << max_val;
    std::cout << "\nAverage of min and max: " << average;
    std::cout << "\nNumber of elements greater than average: " << indices.size();
    std::cout << "\nTheir indices: ";
    for (size_t idx : indices) {
        std::cout << idx << " ";
    }
    std::cout << "\n";
}

/* Read an integer from a file, create an array of this size and fill it with numbers from the file.
   In the array, find elements that are not divisible by any other element of the array.
   Display the result on the screen. */
void task2(Array* arr)
{
    size_t n = array_size(arr);

    // Find elements that are not divisible by any other element
    std::vector<Data> result;

    for (size_t i = 0; i < n; ++i) {
        Data current = array_get(arr, i);
        if (current == 0) continue; // Skip zero

        bool divisible = false;

        for (size_t j = 0; j < n; ++j) {
            if (i != j) {
                Data other = array_get(arr, j);
                if (other != 0 && current % other == 0) {
                    divisible = true;
                    break;
                }
            }
        }

        if (!divisible) {
            result.push_back(current);
        }
    }

    // Display results
    std::cout << "Array: ";
    for (size_t i = 0; i < n; ++i) {
        std::cout << array_get(arr, i) << " ";
    }
    std::cout << "\nElements not divisible by any other element: ";
    for (Data val : result) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input)
    {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }

    // Task 1
    std::cout << "=== Task 1: Elements greater than average of min and max ===" << std::endl;
    Array* arr = array_create_and_read(input);
    task1(arr);
    array_delete(arr);

    // Reset file pointer for Task 2
    input.clear();
    input.seekg(0);

    // Task 2
    std::cout << "\n=== Task 2: Elements not divisible by any other element ===" << std::endl;
    arr = array_create_and_read(input);
    task2(arr);
    array_delete(arr);

    input.close();
    return 0;
}