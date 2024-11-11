#include "list.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 128


void stdin_string (char *string);
int priority_operation(char operand);
void parcing_string_algoritm(char *string ,Stack_operation **stack_operations, Stack **stack_elements);
void print_rpn(Stack **StackElement);


int main(int argc, char **argv) {

    List_element *head_1, *head_2;

    Stack *StackElement = create_stack_element(&head_1, free);
    Stack_operation *StackOperation = create_stack_operation(&head_2, free);

    List_element *list_1;

    char *string = malloc(SIZE * sizeof(char));


    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        perror("Ошибка открытия файла");
        return 1; 
    }

    list_1 = create_list_element(&head_1,free);
    if(list_1 == NULL){
        return -1;
    }


    if(fgets(string, SIZE, input) != NULL){
        /*Вызов функций*/ 
        /*stdin_string (string);*/
        parcing_string_algoritm(string , &StackOperation , &StackElement);

        print_rpn(&StackElement);
    } else {
        printf("Error open file?");
    }

    /* Очищение*/
    free(string);

    free_stack_element(&StackElement);
    free_stack_operation(&StackOperation);

    delete_list_memory_element(&head_1);

    fclose(input);

    return 0;
}


/*void stdin_string (char *string){
    if(fgets(string,SIZE, stdin) != NULL){
        printf("Вы ввели: %s",string);   
    }
}*/


int priority_operation(char operand){
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
        default : 
            flag = -1;
            break;
    }
    return flag;
}


void parcing_string_algoritm(char *string ,Stack_operation **stack_operations, Stack **stack_elements){
    int i = 0;
    for(i = 0; string[i] != '\0'; i ++){
        if(isalpha(string[i])){
            stack_push_element(stack_elements ,string[i]);
        } else if(string[i] == '('){ 
            stack_push_operation(stack_operations,string[i]);
        } else if(string[i] == ')'){
            while(!stack_empty_operation(stack_operations) && stack_peek_operation(stack_operations) -> operation != '('){
                char op = stack_pop_operation(stack_operations);
                stack_push_element(stack_elements, op);
            }
            if (!stack_empty_operation(stack_operations) && stack_peek_operation(stack_operations) -> operation == '('){
                stack_pop_operation(stack_operations);
            }
        } else if (priority_operation(string[i]) > 0){
            while (!stack_empty_operation(stack_operations) && priority_operation(stack_peek_operation(stack_operations) -> operation) >= priority_operation(string[i])){
                char op =stack_pop_operation(stack_operations);
                stack_push_element(stack_elements, op);
            }
            stack_push_operation(stack_operations, string[i]);
        }
    }

    while(stack_peek_operation (stack_operations) != 0){
        char op = stack_pop_operation(stack_operations);
        stack_push_element(stack_elements, op);
    }
}


void print_rpn(Stack **StackElement) {
    Stack *temp_stack = NULL;
    while (*StackElement != NULL) {
        char element = stack_pop_element(StackElement);
        stack_push_element(&temp_stack, element);
    }

    printf("Обратная польская запись: ");
    while (temp_stack != NULL) {
        char element = stack_pop_element(&temp_stack);
        printf("%c", element);
    }
    printf("\n");
}
