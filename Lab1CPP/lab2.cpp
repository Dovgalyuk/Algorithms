#include <iostream>
#include <fstream>
#include <sstream>
#include "list.h"
#include "stack.h"

struct Register {
    int A;
    int B;
    int C;
    int D;

    Register() : A(0), B(0), C(0), D(0) {}
};

int main (int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " input_file" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Fail to open file" << std::endl;
        return -1;
    }

    Stack* stack = stack_create();
    Register registers;
    std::string line;

    bool error = 0;

    while (std::getline(input, line)) {
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "push") {
            std::string value;
            iss >> value;
            if (value == "A" || value == "B" || value == "C" || value == "D") {
                if (value == "A") stack_push(stack, registers.A);
                else if (value == "B") stack_push(stack, registers.B);
                else if (value == "C") stack_push(stack, registers.C);
                else if (value == "D") stack_push(stack, registers.D);
            } else {
                stack_push(stack, std::stoi(value));
            }
        } else if (command == "pop") {
            std::string reg;
            iss >> reg;
            if (stack_empty(stack) || stack_get(stack) == -1) {
                std::cout << "BAD POP" << std::endl;
                error = 1;
                break;
            }
            if (reg == "A") registers.A = stack_get(stack);
            else if (reg == "B") registers.B = stack_get(stack);
            else if (reg == "C") registers.C = stack_get(stack);
            else if (reg == "D") registers.D = stack_get(stack);
            stack_pop(stack);
        } else if (command == "call") {
            stack_push(stack, -1);
        } else if (command == "ret") {
            if (stack_empty(stack) || stack_get(stack) != -1) {
                std::cout << "BAD RET" << std::endl;
                error = 1;
                break;
            }
            stack_pop(stack);
        } else {
            std::cerr << "Unknown command: " << command << std::endl;
            error = 1;
            break;
        }
    }

    if (!error) {
        std::cout << "A = " << registers.A << std::endl;
        std::cout << "B = " << registers.B << std::endl;
        std::cout << "C = " << registers.C << std::endl;
        std::cout << "D = " << registers.D << std::endl;
    }

    stack_delete(stack);
    
    return 0;
}