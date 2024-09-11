#include <iostream>
#include "stack.h"

#define stack_push(stack, s) stack_push((stack), ((Data)(s)))
#define stack_get(stack) ((char)(stack_get((stack))))

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
    size_t index = 0;
    char current_symbol;
    Stack *stack = stack_create();

    while (argv[1][index] != '\0'){
        current_symbol = argv[1][index];

        if (is_operand(current_symbol)) {
            std::cout << current_symbol;
            index++;
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

        index++;
    }

    while (!stack_empty(stack)){
        std::cout << stack_get(stack);
        stack_pop(stack);
    }

    stack_delete(stack);

    return 0;
}
