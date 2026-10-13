#include <iostream>
#include <fstream>
#include <string>
#include "stack.h"

int main(int argc, char* argv[]){
    if (argc < 2) {
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        return 1;
    }

    int max_size = 0;
    if (!(in >> max_size)) return 0;

    Stack* stack = stack_create();
    int current_size = 0;

    std::string command;
    while (in >> command) {
        if (command == "push") {
            int val = 0;
            in >> val;
            if (current_size >= max_size) std::cout << "BAD PUSH\n";
            else {
                stack_push(stack, val);
                current_size++;
            }
        }
        else if (command == "pop") {
            if (stack_empty(stack)) std::cout << "BAD POP\n";
            else {
                std::cout << stack_get(stack) << "\n";
                stack_pop(stack);
                current_size--;
            }
        }
    }

    std::cout << "STACK\n";
    while (!stack_empty(stack)) {
        std::cout << stack_get(stack) << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
    return 0;
}