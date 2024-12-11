#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

struct CPU {
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
};

void execute_instructions(const std::string& filename) {
    Stack* stack = stack_create();
    CPU cpu;
    std::ifstream infile(filename);
    std::string command;
    int value;
    bool error = false;

    while (infile >> command) {
        if (command == "push") {
            infile >> value;
            stack_push(stack, value);
        } else if (command == "pop") {
            char reg;
            infile >> reg;
            if (stack_empty(stack) || stack_get(stack) == -1) {
                std::cout << "BAD POP" << std::endl;
                error = true;
                break;
            } else {
                int popped_value = stack_get(stack);
                stack_pop(stack);
                switch (reg) {
                    case 'A': cpu.A = popped_value; break;
                    case 'B': cpu.B = popped_value; break;
                    case 'C': cpu.C = popped_value; break;
                    case 'D': cpu.D = popped_value; break;
                    default:
                        std::cout << "Invalid register" << std::endl;
                        error = true;
                        break;
                }
            }
        } else if (command == "call") {
            stack_push(stack, -1); // -1 обозначает адрес возврата
        } else if (command == "ret") {
            if (stack_empty(stack) || stack_get(stack) != -1) {
                std::cout << "BAD RET" << std::endl;
                error = true;
                break;
            } else {
                stack_pop(stack);
            }
        }
    }

    if (!error) {
        std::cout << "A = " << cpu.A << std::endl;
        std::cout << "B = " << cpu.B << std::endl;
        std::cout << "C = " << cpu.C << std::endl;
        std::cout << "D = " << cpu.D << std::endl;
    }

    stack_delete(stack);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    execute_instructions(filename);

    return 0;
}
