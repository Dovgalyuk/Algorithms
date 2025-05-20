#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

int main() {
    Stack* stack = stack_create();
    int vars[4] = { 0, 0, 0, 0 };
    std::string line;
    std::ifstream inputFile("input.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        std::cout << "Executing: " << command << std::endl;

        if (command == "bipush") {
            int value;
            ss >> value;
            stack_push(stack, value);
        }
        else if (command == "pop") {
            if (!stack_empty(stack)) {
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty" << std::endl;
            }
        }
        else if (command == "imul") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op1 * op2);
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for imul" << std::endl;
                    stack_push(stack, op2);
                }

            }
            else {
                std::cerr << "Error: Not enough operands on stack for imul" << std::endl;
            }
        }
        else if (command == "iand") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op1 & op2);
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for iand" << std::endl;
                    stack_push(stack, op2);
                }

            }
            else {
                std::cerr << "Error: Not enough operands on stack for iand" << std::endl;
            }
        }
        else if (command == "ior") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op1 | op2);
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for ior" << std::endl;
                    stack_push(stack, op2);
                }

            }
            else {
                std::cerr << "Error: Not enough operands on stack for ior" << std::endl;
            }
        }
        else if (command == "ixor") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op1 ^ op2);
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for ixor" << std::endl;
                    stack_push(stack, op2);
                }

            }
            else {
                std::cerr << "Error: Not enough operands on stack for ixor" << std::endl;
            }
        }
        else if (command == "iadd") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op1 + op2);
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for iadd" << std::endl;
                    stack_push(stack, op2);
                }

            }
            else {
                std::cerr << "Error: Not enough operands on stack for iadd" << std::endl;
            }
        }
        else if (command == "isub") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op1 - op2);
                }
                else {
                    std::cerr << "Error: Not enough operands on stack for isub" << std::endl;
                    stack_push(stack, op2);
                }

            }
            else {
                std::cerr << "Error: Not enough operands on stack for isub" << std::endl;
            }
        }
        else if (command == "iload_0") {
            stack_push(stack, vars[0]);
        }
        else if (command == "iload_1") {
            stack_push(stack, vars[1]);
        }
        else if (command == "iload_2") {
            stack_push(stack, vars[2]);
        }
        else if (command == "iload_3") {
            stack_push(stack, vars[3]);
        }
        else if (command == "istore_0") {
            if (!stack_empty(stack)) {
                vars[0] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_0)" << std::endl;
            }
        }
        else if (command == "istore_1") {
            if (!stack_empty(stack)) {
                vars[1] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_1)" << std::endl;
            }
        }
        else if (command == "istore_2") {
            if (!stack_empty(stack)) {
                vars[2] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_2)" << std::endl;
            }
        }
        else if (command == "istore_3") {
            if (!stack_empty(stack)) {
                vars[3] = stack_get(stack);
                stack_pop(stack);
            }
            else {
                std::cerr << "Error: Stack is empty (istore_3)" << std::endl;
            }
        }
        else if (command == "swap") {
            if (!stack_empty(stack)) {
                int op2 = stack_get(stack);
                stack_pop(stack);
                if (!stack_empty(stack)) {
                    int op1 = stack_get(stack);
                    stack_pop(stack);
                    stack_push(stack, op2);
                    stack_push(stack, op1);
                }
                else {
                    std::cerr << "Error: Not enough elements on stack for swap" << std::endl;
                    stack_push(stack, op2);
                }
            }
            else {
                std::cerr << "Error: Not enough elements on stack for swap" << std::endl;
            }
        }
        else if (command == "invokestatic") {
            int address;
            ss >> address;
            stack_push(stack, -1);
            std::cout << "Calling function at address: " << address << std::endl;
        }
        else if (command == "return") {
            if (!stack_empty(stack)) {
                int returnAddress = stack_get(stack);
                stack_pop(stack);
                if (returnAddress != -1) {
                    std::cerr << "Error: Invalid return address: " << returnAddress << std::endl;
                }
                else {
                    std::cout << "Returning from function" << std::endl;
                }
            }
            else {
                std::cerr << "Error: Return address not found on stack" << std::endl;
            }

        }
        else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }

    inputFile.close();

    std::cout << "stack:" << std::endl;
    Stack* temp_stack = stack_create();
    List* list = stack->list;
    while (list) {
        ListItem* current = list_first(stack->list);
        if (current != nullptr) {
            std::cout << list_item_data(current) << std::endl;
            list = list_erase_first(stack->list);
        }
        else {
            break;
        }
    }
    stack_delete(temp_stack);

    std::cout << "vars:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << vars[i] << std::endl;
    }

    stack_delete(stack);

    return 0;
}