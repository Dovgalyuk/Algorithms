#include "lab2.h"

void task1(FILE *input, Stack* stack, FILE* out) {
    char symbol;

    while (fscanf(input, "%c", &symbol) > 0 && symbol != '\n') {
        if (symbol >= 48 && symbol <= 57) {
            int num = (int)symbol - 48;
            stack_push(stack, num);
        }

        if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%')
            arithmetic_stack(stack, symbol);

        if (symbol == '!')
            inverse_stack(stack);

        if (symbol == '`')
            comparison_stack(stack);

        if (symbol == ':')
            dublicat_stack(stack);

        if (symbol == '.')
            print_stack(stack, out);

        if (symbol == '&')
            cin_stack(stack);
    }
}

void arithmetic_stack(Stack* stack, char symbol) {
    if (stack_size(stack) >= 2) {
        int num1 = stack_get(stack);
        stack_pop(stack);
        int num2 = stack_get(stack);
        stack_pop(stack);
        int res = 0;
        switch (symbol)
        {
        case '+':
            res = num1 + num2;
            stack_push(stack, res);
            break;
        case '-':
            res = num1 - num2;
            stack_push(stack, res);
            break;
        case '*':
            res = num1 * num2;
            stack_push(stack, res);
            break;
        case '/':
            if (num2 != 0) {
                int res = num1 / num2;
                stack_push(stack, res);
            } else {
                throw std::invalid_argument("num2 == 0");
            }
            break;
        case '%':
            res = num1 % num2;
            stack_push(stack, res);
            break;
        default:
            break;
        }
    } else {
        throw std::out_of_range("out of range");
    }
    
}

void inverse_stack(Stack* stack) {
    if (stack_empty(stack)) {
        throw std::out_of_range("out of rage");
    }

    if (stack_get(stack) == 0) {
        stack_pop(stack);
        stack_push(stack, 1);
    } else {
        stack_pop(stack);
        stack_push(stack, 0);
    }
}

void comparison_stack(Stack* stack) {
    if (stack_size(stack) >= 2) {
        int num1 = stack_get(stack);
        stack_pop(stack);
        int num2 = stack_get(stack);
        stack_pop(stack);
        if (num1 > num2) {
            stack_push(stack, 1);
        } else {
            stack_push(stack, 0);
        }
    } else {
        throw std::out_of_range("out of rage");
    }
}

void dublicat_stack(Stack* stack) {
    if (stack_empty(stack)) {
        throw std::out_of_range("out of rage");
    }

    int num = stack_get(stack);
    stack_push(stack, num);
}

void print_stack(Stack* stack, FILE* out) {
    if (stack_empty(stack)) {
        throw std::out_of_range("out of rage");
    }

    int num = stack_get(stack);
    stack_pop(stack);
    fprintf(out, "%d\n", num);
}

void cin_stack(Stack* stack) {
    int num;
    std::cout << "Enter num: ";
    std::cin >> num;
    stack_push(stack, num);
}