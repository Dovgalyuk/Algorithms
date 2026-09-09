#include <fstream>
#include <iostream>
#include "../LibraryCPP/array.h"
#include <limits>

using namespace std;

bool is_palindrome(int number)
{
    int original = number;
    long long reversed = 0;

    while (number > 0)
    {
        int digit = number % 10;
        reversed = reversed * 10 + digit;
        number /= 10;
    }

    return original == reversed;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: palindromes <input_file>\n";
        return 1;
    }

    ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    int size;
    if (!(input >> size) || size < 0)
    {
        std::cerr << "Invalid array size\n";
        return 1;
    }

    // cout << "Array size: " << size << '\n';

    // cout << "121: " << is_palindrome(121) << '\n';
    // cout << "123: " << is_palindrome(123) << '\n';

    Array* arr = array_create(size);

    int index = 0;
    long long number = 1;

    while (index < size && number <= numeric_limits<int>::max())
    {
        int value = static_cast<int>(number);

        if (is_palindrome(static_cast<int>(number)))
        {
            array_set(arr, index, value);
            ++index;
        }
        ++number;
    }

    if (index < size)
    {
        cerr << "Array size is too large for int palindromes\n";
        array_delete(arr);
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        if (i > 0)
            cout << ' ';

            
        cout << array_get(arr, i);
    }

    cout << "\n";

    array_delete(arr);
    return 0;
}