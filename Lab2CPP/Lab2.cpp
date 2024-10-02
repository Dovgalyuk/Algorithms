#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include "stack.h"

const int NUM_REGISTERS = 4;
std::map<std::string, size_t> registers;
Stack* processorStack;  // Используем ваш самописный стек
bool inSubroutine = false;

void initialize_registers() {
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;
}

void push_value(const std::string& value) {
    if (std::isdigit(value[0]) || (value[0] == '-' && value.size() > 1)) {
        stack_push(processorStack, std::stoi(value));
    } else {
        stack_push(processorStack, registers[value]);
    }
}

void pop_value(const std::string& reg) {
    if (stack_empty(processorStack)) {
        std::cout << "BAD POP\n";
        return;
    }

    size_t top_value = stack_get(processorStack);

    if (inSubroutine) {
        std::cout << "BAD POP\n";
        return;
    }

    registers[reg] = top_value;
    stack_pop(processorStack);
}

void call() {
    stack_push(processorStack, SIZE_MAX);
    inSubroutine = true;
}

void ret() {
    if (stack_empty(processorStack)) {
        std::cout << "BAD RET\n";
        return;
    }

    size_t top_value = stack_get(processorStack);

    if (top_value != SIZE_MAX) {
        std::cout << "BAD RET\n";
        return;
    }

    stack_pop(processorStack); 
    inSubroutine = false; 
}

int main() {
    initialize_registers();

    // Инициализация стека
    processorStack = stack_create();

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

    // Освобождение памяти стека
    stack_delete(processorStack);

    return 0;
}
