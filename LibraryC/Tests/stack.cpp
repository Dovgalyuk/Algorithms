#include <iostream>
#include "../stack.h"
#include "../list.h"

void free_func(void* data) {
    free(data);
}

int main() {

    /* Тест стека элементов*/
    Stack_element* stack_element_head = NULL;
    List_element* list_element_head = NULL;

    Stack_element* new_stack_element = create_stack_element(&list_element_head, free_func);
    if (new_stack_element == NULL) {
        std::cerr << "Error: Failed to create stack element." << std::endl;
        return 1;
    }

    stack_push_element(&stack_element_head, 'A');
    stack_push_element(&stack_element_head, 'B');
    stack_push_element(&stack_element_head, 'C');

    std::cout << "Stack elements: ";
    while (stack_element_head != NULL) {
        std::cout << stack_pop_element(&stack_element_head) << " ";
    }
    std::cout << std::endl;

    free_stack_element(&stack_element_head);

    /*Тест стека операций*/
    Stack_operation* stack_operation_head = NULL;
    List_operation* list_operation_head = NULL;

    Stack_operation* new_stack_operation = create_stack_operation(&list_operation_head, free_func);
    if (new_stack_operation == NULL) {
        std::cerr << "Error: Failed to create stack operation." << std::endl;
        return 1;
    }

    stack_push_operation(&stack_operation_head, '+');
    stack_push_operation(&stack_operation_head, '-');
    stack_push_operation(&stack_operation_head, '*');

    std::cout << "Stack operations: ";
    while (stack_operation_head != NULL) {
        std::cout << stack_pop_operation(&stack_operation_head) << " ";
    }
    std::cout << std::endl;

    free_stack_operation(&stack_operation_head);

    return 0;
}