#include "stack.h"
#include "vector.h"

#include <utility>

struct Stack
{
    Vector *vector;
};

Stack *stack_create()
{
    Stack *stack = new Stack;
    stack->vector = vector_create();
    return stack;
    // return new Stack;
}

void stack_delete(Stack *stack)
{
    // TODO: free stack elements
    if (stack)
    {
        vector_delete(stack->vector);  // Освобождаем внутренний vector
        delete stack;
    }
}

void stack_push(Stack *stack, Data data)
{
    if (!stack)
        return;

    size_t current_size = vector_size(stack->vector);
    vector_resize(stack->vector, current_size + 1);
    vector_set(stack->vector, current_size, data);
}

Data stack_get(const Stack *stack)
{
    if (!stack || stack_empty(stack))
    {
        return (Data)0; // Значение по умолчанию для пустого стека
    }

    size_t current_size = vector_size(stack->vector);
    return vector_get(stack->vector, current_size - 1);
}

Data stack_pop(Stack *stack)
{
    if (!stack || stack_empty(stack))
        return (Data)0;

    size_t current_size = vector_size(stack->vector);

    Data value = vector_get(stack->vector, current_size - 1);
    vector_resize(stack->vector, current_size - 1);
    return value;
}

bool stack_empty(const Stack *stack)
{
    if (!stack)
        return true;

    return vector_size(stack->vector) == 0;
}

size_t stack_size(const Stack *stack)
{
    if (!stack)
        return 0;

    return vector_size(stack->vector);
}

void stack_reverse(Stack *stack)
{
    if (!stack)
        return;

    // перекладываем элементы во второй стек: теперь наверху бывший нижний элемент
    Stack *reversed = stack_create();

    while (!stack_empty(stack))
        stack_push(reversed, stack_pop(stack));

    // обмен указателей: stack получает развёрнутые элементы
    std::swap(stack->vector, reversed->vector);

    stack_delete(reversed);
}