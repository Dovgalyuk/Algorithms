#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

int main() {
    Stack* stack = stack_create();
    int variables[4] = { 0, 0, 0, 0 };

    std::ifstream inputFile("input.txt"); //D:\VisualStudioRepo\Algorithms\out\build\x64-debug\Labs - мое расположения файла. Он должен быть там, где собирается .exe файл решения
    if (!inputFile.is_open()) {
        std::cerr << "Failed open!" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string operation;
        iss >> operation;

        if (operation == "bipush") {
            int value;
            if (iss >> value) {
                stack_push(stack, value);
            }
        }
        else if (operation == "pop") {
            stack_pop(stack);
        }
        else if (operation == "imul") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a * b);
        }
        else if (operation == "iand") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a & b);
        }
        else if (operation == "ior") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a | b);
        }
        else if (operation == "ixor") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a ^ b);
        }
        else if (operation == "iadd") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a + b);
        }
        else if (operation == "isub") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, b - a);
        }
        else if (operation == "iload_0") {
            stack_push(stack, variables[0]);
        }
        else if (operation == "iload_1") {
            stack_push(stack, variables[1]);
        }
        else if (operation == "iload_2") {
            stack_push(stack, variables[2]);
        }
        else if (operation == "iload_3") {
            stack_push(stack, variables[3]);
        }
        else if (operation == "istore_0") {
            variables[0] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "istore_1") {
            variables[1] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "istore_2") {
            variables[2] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "istore_3") {
            variables[3] = stack_get(stack);
            stack_pop(stack);
        }
        else if (operation == "swap") {
            int a = stack_get(stack);
            stack_pop(stack);
            int b = stack_get(stack);
            stack_pop(stack);
            stack_push(stack, a);
            stack_push(stack, b);
        }
    }
    inputFile.close();

    std::cout << "stack:" << std::endl;
    while (!stack_empty(stack)) {
        std::cout << stack_get(stack) << std::endl;
        stack_pop(stack);
    }

    std::cout << "vars:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << variables[i] << std::endl;
    }

    stack_delete(stack);

    return 0;
}