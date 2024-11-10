#include <iostream>
#include "stack.h"
#include "list.h"

void free_func(void* data) {
    free(data);
}


void free_stack_element_test(Stack** stack_head);
void free_stack_operation_test(Stack_operation** stack_head);


int main() {
    /* Тест стека элементов*/
    Stack* stack_element_head = NULL;

    stack_push_element(&stack_element_head, 'A');
    stack_push_element(&stack_element_head, 'B');
    stack_push_element(&stack_element_head, 'C');

    std::cout << "Stack elements: ";
    while (stack_element_head != NULL) {
        std::cout << stack_pop_element(&stack_element_head) << " ";
    }
    std::cout << std::endl;

    while (stack_element_head != NULL) {
        Stack* temp = stack_element_head;
        stack_element_head = stack_element_head->next;
        free(temp);
    }

    /*Тест стека операций*/
    Stack_operation* stack_operation_head = NULL;

    stack_push_operation(&stack_operation_head, '+');
    stack_push_operation(&stack_operation_head, '-');
    stack_push_operation(&stack_operation_head, '*');

    std::cout << "Stack operations: ";
    while (stack_operation_head != NULL) {
        std::cout << stack_pop_operation(&stack_operation_head) << " ";
    }
    std::cout << std::endl;

    while (stack_operation_head != NULL) {
        Stack_operation* temp = stack_operation_head;
        stack_operation_head = stack_operation_head->next;
        free(temp);
    }

    return 0;
}


void free_stack_element_test(Stack** stack_head){
    while(*stack_head != NULL){
        Stack* temp = *stack_head;
        *stack_head = (*stack_head) -> next;
        delete temp;
    }
}


void free_stack_operation_test(Stack_operation** stack_head){
    while(*stack_head != NULL){
        Stack_operation* temp = *stack_head;
        *stack_head = (*stack_head) -> next;
        delete temp;
    }
}
