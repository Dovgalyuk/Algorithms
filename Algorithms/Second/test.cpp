#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.cpp"

std::string to_lower(std::string str) {
    std::string new_str;
    for (char i : str) {
        new_str += (char) tolower(i);
    }
    return new_str;
}

int main() {
    Stack* stack = stack_create();
    std::ifstream is("../../../Algorithms/Second/input.txt");
    std::ofstream os("../../../Algorithms/Second/output.txt");
    if (is.is_open() && os.is_open()) {
        std::string line;
        while (is >> line) {
            int index = line.find('/');
            if (index < line.length()) {
                if (!stack_empty(stack) && stack_get(stack) == to_lower(line.replace(index, 1, ""))) {
                    stack_pop(stack);
                }
            } else {
                stack_push(stack, to_lower(line));
            }
        }
        os << (stack_empty(stack) ? "YES" : "NO");
        os.flush();
        os.close();
    } else {
        std::cout << "error";
    }
    return 0;
}