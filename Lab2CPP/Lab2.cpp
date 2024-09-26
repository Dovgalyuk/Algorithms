#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <stack>

const int NUM_REGISTERS = 4;
std::map<std::string, int> registers;
std::stack<int> processorStack;
bool inSubroutine = false;

void initialize_registers() {
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;
}

void push_value(const std::string& value) {
    if (std::isdigit(value[0]) || (value[0] == '-' && value.size() > 1)) {
        processorStack.push(std::stoi(value));
    } else {
        processorStack.push(registers[value]);
    }
}

void pop_value(const std::string& reg) {
    if (processorStack.empty()) {
        std::cout << "BAD POP\n";
        return;
    }

    int top_value = processorStack.top();

    if (inSubroutine) {
        std::cout << "BAD POP\n";
        return;
    }

    registers[reg] = top_value;
    processorStack.pop();
}

void call() {
    processorStack.push(-1);
    inSubroutine = true;
}

void ret() {
    if (processorStack.empty()) {
        std::cout << "BAD RET\n";
        return;
    }

    int top_value = processorStack.top();

    if (top_value != -1) {
        std::cout << "BAD RET\n";
        return;
    }

    processorStack.pop(); 
    inSubroutine = false; 
}

int main() {
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

    return 0;
}
