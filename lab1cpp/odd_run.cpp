#include "utils.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: Lab1OddRun <input_file>\n";
        return 1;
    }

    try {
        MyArray arr = readArrayFromFile(argv[1]);

        int maximumLength = 0;
        int currentLength = 0;

        for (std::size_t i = 0; i < arr.size(); ++i) {
            if (arr.get(i) % 2 != 0) {
                ++currentLength;

                if (currentLength > maximumLength) {
                    maximumLength = currentLength;
                }
            } else {
                currentLength = 0;
            }
        }

        std::cout << maximumLength << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}