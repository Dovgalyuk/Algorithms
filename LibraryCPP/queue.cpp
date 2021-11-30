#include "queue.h"
#include "stack.h"

struct Queue
{
    Stack* inStack;
    Stack* stack;
    Queue() {
        inStack = stack_create();
        stack = stack_create();
    }
};

Queue* queue_create()
{
    return new Queue;
}

void queue_delete(Queue* queue)
{
    // TODO: free queue items
    stack_delete(queue->inStack);
    stack_delete(queue->stack);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    if (queue_empty(queue)) {
        stack_push(queue->stack, data);
    }
    else {
        while (!stack_empty(queue->stack)) {
            stack_push(queue->inStack, stack_get(queue->stack));
            stack_pop(queue->stack);
        }
        stack_push(queue->stack, data);
        while (!stack_empty(queue->inStack)) {
            stack_push(queue->stack, stack_get(queue->inStack));
            stack_pop(queue->inStack);
        }

    }

}

Data queue_get(const Queue* queue)
{
    return stack_get(queue->stack);
}

void queue_remove(Queue* queue)
{
    stack_pop(queue->stack);
}

bool queue_empty(const Queue* queue)
{
    return ((stack_empty(queue->stack)));
}
