#include "queue.h"
#include "stack.h"

struct Queue
{
    Stack *oneStack = nullptr;
    Stack *twoStack = nullptr;

    Queue() {
        oneStack = stack_create();
        twoStack = stack_create();
    }

    ~Queue() {
        stack_delete(oneStack);
        stack_delete(twoStack);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    stack_push(queue->oneStack, data);
}

void add_data_twoStack(Queue *queue) {

    if (stack_empty(queue->twoStack)) {

        while(!stack_empty(queue->oneStack)) {
            stack_push(queue->twoStack, stack_get(queue->oneStack));
            stack_pop(queue->oneStack);
        }
    }
}

Data queue_get(Queue *queue)
{
    add_data_twoStack(queue);
    
    return stack_get(queue->twoStack);
}

void queue_remove(Queue *queue)
{

    if (queue_empty(queue)) {
        return;
    }

    add_data_twoStack(queue);

    stack_pop(queue->twoStack);
}

bool queue_empty(const Queue *queue)
{
    return stack_empty(queue->twoStack) && stack_empty(queue->oneStack);
}