#include <fstream>
#include <iostream>
#include "../LibraryCPP/array.h"


using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: rle <input_file>\n";
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

    Array* arr = array_create(size);

    for (int i = 0; i < size; ++i)
    {
        int value;
        if (!(input >> value))
        {
            std::cerr << "Invalid input data\n";
            array_delete(arr);
            return 1;
        }
        array_set(arr, i, value);
    }


    // for (int i = 0; i < size; ++i)
    // {
    //     if (i > 0)
    //         cout << " ";

    //     cout << array_get(arr, i);
    // }

    if (size > 0)
    {
        int current = array_get(arr, 0);
        int count = 1;

        for (int i = 1; i < size; ++i)
        {
            int value = array_get(arr, i);
            if (value == current)
            {
                ++count;
            }
            else
            {
                cout << current << " " << count << "\n";

                current = value;
                count = 1;
            }
        }

        // Output the last value and its count
        cout << current << " " << count << "\n";
    }

    cout << "\n";

    array_delete(arr);
    return 0;
}