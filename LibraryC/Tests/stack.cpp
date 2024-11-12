#include <iostream>
#include "stack.h"

// Функция для освобождения памяти, если это необходимо
void dummy_free(void* ptr) {

}

int main() {
    // Создаем стек
    Stack* stack = create_stack(nullptr, dummy_free);
    if (!stack) {
        std::cerr << "Failed to create stack" << std::endl;
        return 1;
    }

    // Добавляем элементы в стек
    stack_push(stack, 'A');
    stack_push(stack, 'B');
    stack_push(stack, 'C');

    // Выводим элементы стека
    std::cout << "Stack elements: ";
    while (!stack_is_empty(stack)) {
        Data element = stack_pop(stack);
        std::cout << element << " ";
    }
    std::cout << std::endl;

    free_stack(stack);

    return 0;
}
