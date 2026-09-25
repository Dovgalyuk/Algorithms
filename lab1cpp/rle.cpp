#include "utils.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: Lab1RLE <input_file>\n";
        return 1;
    }

    try {
        MyArray arr = readArrayFromFile(argv[1]);

        if (arr.size() == 0) {
            return 0;
        }

        int currentValue = arr.get(0);
        int count = 1;

        for (std::size_t i = 1; i < arr.size(); ++i) {
            if (arr.get(i) == currentValue) {
                ++count;
            } else {
                std::cout << count << ' ' << currentValue << '\n';

                currentValue = arr.get(i);
                count = 1;
            }
        }

        std::cout << count << ' ' << currentValue << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
