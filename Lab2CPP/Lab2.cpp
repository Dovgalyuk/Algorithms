#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include "stack.h"

const int NUM_REGISTERS = 4;
std::map<std::string, int> registers;
Stack* stack;

void initialize_registers() {
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;
}

void push_value(const std::string& value) {
    stack_push(stack, std::stoi(value));
}

void pop_value(const std::string& reg) {
    if (stack_empty(stack)) {
        std::cout << "Stack empty\n";
        return;
    }

    Data top_value = stack_get(stack);
    
    if (top_value < 0) {
        std::cout << "Stack empty\n";
        return;
    }

    registers[reg] = top_value;
    stack_pop(stack);
}

void call() {
        stack_push(stack, -1);
}

void ret() {
    if (stack_empty(stack)) {
        std::cout << "Stack empty\n";
        return;
    }

    Data top_value = stack_get(stack);
    
    if (top_value >= 0) {
        std::cout << "Stack empty\n";
        return;
    }

    stack_pop(stack);
}

int main() {
    
    stack = stack_create();
    initialize_registers();

    std::ifstream input("input2.txt");
    std::string command;
    
    while (std::getline(input, command)) {
        std::istringstream iss(command);
        std::string operation;
        std::string arg;

        iss >> operation;
        if (operation == "push") {
            iss >> arg;
            push_value(arg);
        } else if (operation == "pop") {
            iss >> arg;
            pop_value(arg);
        } else if (operation == "call") {
            call();
        } else if (operation == "ret") {
            ret();
        }
    }

    for (const auto& reg : registers) {
        std::cout << reg.first << " = " << reg.second << std::endl;
    }

    stack_delete(stack);

    return 0;
}
