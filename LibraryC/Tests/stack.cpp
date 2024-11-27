#include <iostream> 
#include "stack.h" 

// Функция для освобождения памяти, выделенной под данные в стеке
void myfree(void *p)
{
    delete (int*)p; // Приводим указатель к типу int и освобождаем память
}

// Функция для получения значения типа int из стека
int stack_get_int(Stack *s)
{
    void *v = stack_get(s); // Получаем верхний элемент стека
    if (!v) // Проверяем, не равен ли указатель NULL
    {
        std::cout << "Invalid stack_get\n"; 
        stack_delete(s); // Освобождаем память, занятую стеком
        exit(1);
    }
    return *(int*)v; // Возвращаем значение по указателю, приводя его к типу int
}

int main()
{
    Stack *stack = stack_create(); // Создаем стек
    std::cout << "Stack create done!\n" << std::endl;

    // Добавляем значения в стек
    stack_push(stack, new int(1));
    stack_push(stack, new int(2));
    stack_push(stack, new int(3));
    std::cout << "Stack push done!\n" << std::endl;

    // Проверяем, правильно ли работает получение верхнего элемента стека
    if (stack_get_int(stack) != 3)
    {
        std::cout << "Invalid stack top after push\n"; 
        stack_delete(stack); // Освобождаем память, занятую стеком
        return 1;
    }

    std::cout << "Get: " << stack_get_int(stack) << "\n"; // Выводим значение верхнего элемента
    delete (int*)stack_pop(stack); // Удаляем верхний элемент стека
    // Проверяем, правильно ли обновился верхний элемент
    if (stack_get_int(stack) != 2)
    {
        std::cout << "Invalid stack top after pop\n"; 
        stack_delete(stack); // Освобождаем память, занятую стеком
        return 1;
    }

    std::cout << "Get: " << stack_get_int(stack) << "\n"; // Выводим значение верхнего элемента
    delete (int*)stack_pop(stack); // Удаляем верхний элемент стека
    // Проверяем, правильно ли обновился верхний элемент
    if (stack_get_int(stack) != 1)
    {
        std::cout << "Invalid stack top after pop\n"; 
        stack_delete(stack); // Освобождаем память, занятую стеком
        return 1; 
    }

    std::cout << "Get: " << stack_get_int(stack) << "\n"; // Выводим значение верхнего элемента
    // Добавляем новые значения в стек
    stack_push(stack, new int(4));
    stack_push(stack, new int(5));

    // Проверяем, правильно ли работает получение верхнего элемента стека
    if (stack_get_int(stack) != 5)
    {
        std::cout << "Invalid stack top after push\n"; 
        stack_delete(stack); // Освобождаем память, занятую стеком
        return 1;
    }

    // Извлекаем и выводим все элементы из стека
    while (!stack_empty(stack))
    {
        std::cout << "Get: " << stack_get_int(stack) << "\n"; // Получаем и выводим верхний элемент
        delete (int*)stack_pop(stack); // Удаляем верхний элемент стека
    }

    stack_delete(stack); // Освобождаем память, занятую стеком
}
