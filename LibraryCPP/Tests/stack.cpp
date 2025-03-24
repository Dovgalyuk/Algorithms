#include <iostream>
#include "stack.h"

int main() {
    Stack* stack = stack_create();

    // Вставляем теги вместо чисел
    stack_push(stack, "<html>");
    stack_push(stack, "<body>");
    stack_push(stack, "<h1>");

    if (stack_get(stack) != "<h1>") {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);

    if (stack_get(stack) != "<body>") {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_pop(stack);

    if (stack_get(stack) != "<html>") {
        std::cout << "Invalid stack top after pop\n";
        stack_delete(stack);
        return 1;
    }

    std::cout << "Get: " << stack_get(stack) << "\n";
    stack_push(stack, "<p>");
    stack_push(stack, "<footer>");

    if (stack_get(stack) != "<footer>") {
        std::cout << "Invalid stack top after push\n";
        stack_delete(stack);
        return 1;
    }

    while (!stack_empty(stack)) {
        std::cout << "Get: " << stack_get(stack) << "\n";
        stack_pop(stack);
    }

    stack_delete(stack);
    return 0;
}