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
    stack_push(stack, static_cast<Data>(std::stoi(value))); // Приведение к Data
}

void pop_value(const std::string& reg) {
    if (stack_empty(stack)) {
        std::cout << "Stack empty\n";
        return;
    }

    Data top_value = stack_get(stack);

    // Здесь мы проверяем на специальное значение -1
    if (top_value == static_cast<Data>(-1)) {
        std::cout << "Stack empty\n";
        return;
    }

    registers[reg] = static_cast<int>(top_value); // Явное преобразование
    stack_pop(stack);
}

void call() {
    stack_push(stack, static_cast<Data>(-1)); // Приведение к Data
}

void ret() {
    if (stack_empty(stack)) {
        std::cout << "Stack empty\n";
        return;
    }

    Data top_value = stack_get(stack);

    // Проверка на специальное значение -1
    if (top_value == static_cast<Data>(-1)) {
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
