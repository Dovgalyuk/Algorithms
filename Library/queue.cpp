#include <stdlib.h>
#include "queue.h"
#include "deque.h"

struct Queue
{
	Deque* deque;
};

Queue *queue_create()
{
	Queue* newQueue = new Queue();
	newQueue->deque = deque_create();
    return newQueue;
}

void queue_delete(Queue *queue)
{
	deque_delete(queue->deque);
	delete queue;
}

void queue_insert(Queue *queue, Data data)
{
	deque_push_back(queue->deque, data);
}

Data queue_get(const Queue *queue)
{
    return deque_first(queue->deque);
}

void queue_remove(Queue *queue)
{
	deque_pop_front(queue->deque);
}

bool queue_empty(const Queue *queue)
{
    return deque_empty(queue->deque);
}
