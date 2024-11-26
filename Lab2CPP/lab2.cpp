#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    if (!input_file) {
        std::cerr << "Error opening file: " << argv[1] << std::endl;
        return 1;
    }

    int max_size;
    input_file >> max_size;

    Stack* stack = stack_create();
    int current_size = 0;

    std::string command;
    while (input_file >> command) {
        if (command == "push") {
            int value;
            input_file >> value;
            if (current_size < max_size) {
                stack_push(stack, value);
                current_size++;
            }
            else {
                std::cout << "BAD PUSH" << std::endl;
            }
        }
        else if (command == "pop") {
            if (!stack_empty(stack)) {
                std::cout << stack_get(stack) << std::endl;
                stack_pop(stack);
                current_size--;
            }
            else {
                std::cout << "BAD POP" << std::endl;
            }
        }
    }

    stack_print(stack);
    stack_delete(stack);
    return 0;
}
