// Дополнительный тест очереди №1: пустая очередь и порядок FIFO
#include <iostream>
#include "queue.h"

int fail(const char *msg)
{
    std::cout << "Error: " << msg << "\n";
    return 1;
}

int main()
{
    Queue *queue = queue_create();

    // новая очередь пустая
    if (!queue_empty(queue))
        return fail("new queue must be empty");

    // один элемент
    queue_insert(queue, 42);
    if (queue_empty(queue) || queue_get(queue) != 42)
        return fail("queue with one element");
    queue_remove(queue);
    if (!queue_empty(queue))
        return fail("queue must be empty after removing the only element");

    // первым пришёл, первым ушёл
    for (int i = 1; i <= 5; i++)
        queue_insert(queue, i);
    for (int i = 1; i <= 5; i++)
    {
        if (queue_get(queue) != i)
            return fail("wrong FIFO order");
        queue_remove(queue);
    }
    if (!queue_empty(queue))
        return fail("queue must be empty at the end");

    queue_delete(queue);

    std::cout << "Queue FIFO test passed\n";
    return 0;
}
