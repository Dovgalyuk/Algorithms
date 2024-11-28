#include <iostream>
#include <string>
#include <vector>
#include "solutions.h"

int main(int argc, char **argv)
{
    if (argc > 1) {
        if (!std::freopen(argv[1], "r", stdin)) {
            std::cout << "Could not open the file\n";
            return 1;
        }
    }

    std::string expression;
    std::vector<int> numbers;
    std::vector<char> operations;

    std::cout << "Enter expression: ";
    std::cin >> expression;

    int num = 0;
    for (char c: expression) {
        if (('0' <= c) and (c <= '9')) {
            num *= 10;
            num += c - '0';
        } else {
            numbers.push_back(num);
            operations.push_back(c);
            num = 0;
        }
    }
    numbers.push_back(num);

    Ans ans1 = solve1(numbers, operations);
    std::cout << ans1.value << '\n' << ans1.expression << std::endl;
    std::cout << std::endl;

    Ans ans2 = solve2(numbers, operations);
    std::cout << ans2.value << '\n' << ans2.expression << std::endl;

    return 0;
}
