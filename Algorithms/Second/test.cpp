#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.h"

std::string to_lower(std::string str) {
    std::string new_str;
    for (char i : str) {
        new_str += (char) tolower(i);
    }
    return new_str;
}

void write(bool answer) {
    std::ofstream os("../../../Algorithms/Second/output.txt");
    if (os.is_open()) {
        os << (answer ? "YES" : "NO");
        os.flush();
        os.close();
    }
}

int main() {
    auto* stack = new Stack<std::string>();
    std::ifstream is("../../../Algorithms/Second/input.txt");
    if (is.is_open()) {
        std::string line;
        while (is >> line) {
            int index = line.find('/');
            if (index < line.length()) {
                if (!stack->empty() && stack->get() == to_lower(line.replace(index, 1, ""))) {
                    stack->pop();
                } else {
                    write(false);
                    return 0;
                }
            } else {
                stack->push(to_lower(line));
            }
        }
        write(stack->empty());
    } else {
        std::cout << "error";
    }
    return 0;
}