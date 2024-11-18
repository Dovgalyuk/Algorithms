#include "list.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 128

void parcing_string_algoritm(char *string, Stack **stack_operations, Stack **stack_elements);
void print_rpn(Stack *stack_elements);

int main(int argc, char **argv) {
    List_element *head = NULL;
    Stack *stack_operations = NULL;
    Stack *stack_elements = NULL;


    char *string = malloc(SIZE * sizeof(char));

    // Создание стека для операций и элементов
    stack_operations = create_stack(NULL);
    stack_elements = create_stack(NULL);

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Ошибка открытия файла");
        free(string);
        free_stack(stack_operations);
        free_stack(stack_elements);
        return 1;
    }

    if (fgets(string, SIZE, input) != NULL) {
        /* Вызов функций */
        parcing_string_algoritm(string, &stack_operations, &stack_elements);
        print_rpn(stack_elements);
    } else {
        printf("Ошибка чтения из файла\n");
    }

    /* Очищение */
    free(string);
    free_stack(stack_operations);
    free_stack(stack_elements);
    delete_list_memory_element(&head);
    fclose(input);

    return 0;
}
int priority_operation(char operand) {
    int flag = -1;
    switch (operand) {
        case '+':
        case '-':
            flag = 1;
            break;
        case '*':
        case '/':
            flag = 2;
            break;
        case '(':
        case ')':
            flag = 0;
            break;
        default:
            flag = -1;
            break;
    }
    return flag;
}

void parcing_string_algoritm(char *string, Stack **stack_operations, Stack **stack_elements) {
    int i = 0;
    for (i = 0; string[i] != '\0'; i++) {
        if (isalpha(string[i])) {
            stack_push(*stack_elements, string[i]);
        } else if (string[i] == '(') {
            stack_push(*stack_operations, string[i]);
        } else if (string[i] == ')') {
            while (!stack_is_empty(*stack_operations) && stack_get(*stack_operations) != '(') {
                char op = stack_pop(*stack_operations);
                stack_push(*stack_elements, op);
            }
            if (!stack_is_empty(*stack_operations) && stack_get(*stack_operations) == '(') {
                stack_pop(*stack_operations);
            }
        } else if (priority_operation(string[i]) > 0) {
            while (!stack_is_empty(*stack_operations) && priority_operation(stack_get(*stack_operations)) >= priority_operation(string[i])) {
                char op = stack_pop(*stack_operations);
                stack_push(*stack_elements, op);
            }
            stack_push(*stack_operations, string[i]);
        }
    }

    while (!stack_is_empty(*stack_operations)) {
        char op = stack_pop(*stack_operations);
        stack_push(*stack_elements, op);
    }
}

void print_rpn(Stack *stack_elements) {
    Stack *temp_stack = create_stack(NULL, free); // Инициализация temp_stack

    if (temp_stack == NULL) {
        perror("Ошибка выделения памяти для временного стека");
        return;
    }

    while (!stack_is_empty(stack_elements)) {
        char element = stack_pop(stack_elements);
        stack_push(temp_stack, element);
    }

    printf("Обратная польская запись: ");
    while (!stack_is_empty(temp_stack)) {
        char element = stack_pop(temp_stack);
        printf("%c", element);
    }
    printf("\n");

    free_stack(temp_stack); // Освобождение памяти для временного стека
}
