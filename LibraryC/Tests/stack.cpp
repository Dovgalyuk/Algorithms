#include <iostream>
#include "stack.h"

// Функция для освобождения памяти, если это необходимо
void dummy_free(void* ptr) {

}

int main() {
    // Создаем стек
    Stack* stack = create_stack(dummy_free);
    if (!stack) {
        std::cerr << "Failed to create stack" << std::endl;
        return 1;
    }

    // Добавляем элементы в стек
    stack_push(stack, 'A');
    stack_push(stack, 'B');
    stack_push(stack, 'C');

    char expected_elements[] = {'C', 'B', 'A'};
    int is_correct = 1;

    // Выводим элементы стека
    std::cout << "Stack elements: ";
    for (int i = 0; i < 3; i++) {
        if (stack_is_empty(stack)) {
            std::cerr << "Error: Stack is empty" << std::endl;
            is_correct = 0;
            break;
        }
        Data element = stack_pop(stack);
        std::cout << element << " ";
        if (element != expected_elements[i]) {
            std::cerr << "\nError: Expected " << expected_elements[i] << " but got " << element << std::endl;
            is_correct = 0;
        }
    }
    std::cout << std::endl;

    free_stack(stack);

    return is_correct ? 0 : 1;
}

