#include "../LibraryC/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

void perform_operation(Stack *stack, char op) {
    int a = (int)(intptr_t)stack_get(stack);
    stack_pop(stack);
    int b = (int)(intptr_t)stack_get(stack);
    stack_pop(stack);

    int result;
    switch (op) {
        case '+': result = b + a; break;
        case '-': result = b - a; break;
        case '*': result = b * a; break;
        case '/': result = b / a; break;
        case '%': result = b % a; break;
        default: return;
    }

    stack_push(stack, (Data)(intptr_t)result);
}

void perform_logical_operation(Stack *stack, char op) {
    int a = (int)(intptr_t)stack_get(stack);
    stack_pop(stack);

    int result;
    switch (op) {
        case '!': result = a == 0 ? 1 : 0; break;
        case '`': {
            int b = (int)(intptr_t)stack_get(stack);
            stack_pop(stack);
            result = a > b ? 1 : 0;
            break;
        }
        default: return;
    }

    stack_push(stack, (Data)(intptr_t)result);
}

void execute_command(Stack *stack, char command) {
    if (isdigit(command)) {
        stack_push(stack, (Data)(intptr_t)(command - '0'));
    } else {
        switch (command) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                perform_operation(stack, command);
                break;
            case '!':
            case '`':
                perform_logical_operation(stack, command);
                break;
            case ':': {
                int a = (int)(intptr_t)stack_get(stack);
                stack_push(stack, (Data)(intptr_t)a);
                break;
            }
            case '.': {
                int a = (int)(intptr_t)stack_get(stack);
                stack_pop(stack);
                printf("%d\n", a);
                break;
            }
            case '&': {
                int input;
                printf("Введите число: ");
                scanf("%d", &input);
                stack_push(stack, (Data)(intptr_t)input);
                break;
            }
        }
    }
}

int main(int argc, char **argv) {
    FILE *input = fopen(argv[1], "r");

    if (!input) {
        printf("Ошибка: Не удалось открыть файл input.txt.\n");
        return 1;
    }

    Stack *stack = stack_create(NULL);
    if (!stack) {
        fclose(input);
        return 1;
    }

    char command;
    while ((command = fgetc(input)) != EOF) {
        if (command == '\n') continue;
        execute_command(stack, command);
    }

    fclose(input);
    stack_delete(stack);
    return 0;
}
