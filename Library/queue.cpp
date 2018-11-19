#include <stdlib.h>
#include "queue.h"
#include "stack.h"

struct Queue
{
	Stack *s1, *s2;
};

Queue *queue_create()
{
	Queue *queue = new Queue();
	queue->s1 = stack_create();
	queue->s2 = stack_create();
    return queue;
}

void queue_delete(Queue *queue)
{
	stack_delete(queue->s1);
	stack_delete(queue->s2);
	delete queue;
}

void queue_insert(Queue *queue, Data data)
{
	stack_push(queue->s1, data);
}

Data queue_get(Queue *queue)
{
	if (stack_empty(queue->s2)) {
		queue_copy(queue);
	}
	if (stack_empty(queue->s2)) {
		return 2;
	}
	else {
		return stack_get(queue->s2);
	}
}

void queue_remove(Queue *queue)
{
	if (stack_empty(queue->s2)) {
		queue_copy(queue);
	}
	if (!stack_empty(queue->s2)) {
		stack_pop(queue->s2);
	}
}

bool queue_empty(const Queue *queue)
{
	if (stack_empty(queue->s1) && stack_empty(queue->s2)) return true;
	return false;
}

void queue_copy(Queue *queue) {
	while (!stack_empty(queue->s1)) {
		stack_push(queue->s2, stack_get(queue->s1));
		stack_pop(queue->s1);
	}
}