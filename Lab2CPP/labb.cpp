#include "stack.h"
#include <iostream>
#include <sstream>
#include <map>

int main() {
    Stack stack;
    std::map<char, int> registers = {{'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}};

    std::string input;
    std::getline(std::cin, input);
    std::istringstream stream(input);
    std::string command;

    while (stream >> command) {
        if (command == "PUSH") {
            std::string param;
            stream >> param;
            // Используем тернарный оператор для упрощения
            stack.push(std::isdigit(param[0]) ? std::stoi(param) : registers[param[0]]);
        } else if (command == "POP") {
            char reg;
            stream >> reg;
            registers[reg] = stack.top();
            stack.pop();
        } else if (command == "ADD") {
            char reg;
            stream >> reg;
            int op1 = stack.top(); stack.pop();
            int op2 = stack.top(); stack.pop();
            registers[reg] = op1 + op2;
        } else if (command == "MUL") {
            char reg;
            stream >> reg;
            int op1 = stack.top(); stack.pop();
            int op2 = stack.top(); stack.pop();
            registers[reg] = op1 * op2;
        } else if (command == "SUB") {
            char reg;
            stream >> reg;
            int op1 = stack.top(); stack.pop();
            int op2 = stack.top(); stack.pop();
            registers[reg] = op1 - op2;
        }
    }

    for (const auto& [reg, value] : registers) {
        std::cout << reg << " = " << value << " ";
    }
    std::cout << std::endl;

    return 0;
}
