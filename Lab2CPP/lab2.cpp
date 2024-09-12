#include <iostream>
#include "stack.h"


bool is_operand(const char symbol)
{
    if (symbol == '+') return false;
    if (symbol == '-') return false;
    if (symbol == '*') return false;
    if (symbol == '/') return false;
    if (symbol == '(') return false;
    if (symbol == ')') return false;

    return true;
}


int main(int argc, char **argv)
{
    char current_symbol;
    char *p = argv[1];
    Stack *stack = stack_create();

    while (*p != '\0'){
        current_symbol = *(p++);

        if (is_operand(current_symbol)) {
            std::cout << current_symbol;
            continue;
        }

        switch (current_symbol){
        case '/':
        case '*':
            if (!stack_empty(stack)){
                if ((stack_get(stack) == '*') || (stack_get(stack) == '/')){
                    std::cout << stack_get(stack);
                    stack_pop(stack);
                }
            }

            stack_push(stack, current_symbol);
            break;

        case '-':
        case '+':
            if (!stack_empty(stack)){
                if ((stack_get(stack) == '*') || (stack_get(stack) == '/')){
                    std::cout << stack_get(stack);
                    stack_pop(stack);
                }
            }

            if (!stack_empty(stack)){
                if ((stack_get(stack) == '+') || (stack_get(stack) == '-')){
                    std::cout << stack_get(stack);
                    stack_pop(stack);
                }
            }

            stack_push(stack, current_symbol);
            break;

        case '(':
            stack_push(stack, current_symbol);
            break;

        case ')':
            while (stack_get(stack) != '('){
                std::cout << stack_get(stack);
                stack_pop(stack);
            }
            
            stack_pop(stack);
        }
    }

    while (!stack_empty(stack)){
        std::cout << stack_get(stack);
        stack_pop(stack);
    }

    stack_delete(stack);

    return 0;
}
