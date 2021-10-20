#include <iostream>
#include "stack.h"
#include <string>

int main() {
    Stack *stack = stack_create();

    int maxSize;
    std::cin >> maxSize;
    std::string cmd;
    do {
        //std::cout << "current: "<< cmd << "\n";
        std::cin >> cmd;
        if (cmd == "push"){
            int data;
            std::cin >> data;
            if (stack_size(stack) == maxSize) {
                std::cout << "BAD PUSH\n";
            } 
            else {
                stack_push(stack, data);
            }
        }
        if (cmd == "pop") {
            if (stack_empty(stack)) {
                std::cout << "BAD POP\n";
            } else {
                stack_pop(stack);
            }
        }
    }  while (cmd != "end");
    
    std::cout << stack_size(stack) << "\nSTACK\n";
    while (stack_size(stack) > 0) {
        std::cout << stack_get(stack) << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
    return 0;
}