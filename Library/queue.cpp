#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* vector;
	size_t head, size;
};

Queue *queue_create()
{
	Queue* queue = new Queue;
	queue->vector = vector_create();
	queue->size = 0;
	queue->head = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
	delete[] queue;
}

void queue_insert(Queue *queue, Data data)
{
	vector_set(queue->vector, queue->size, data);
	queue->size++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
	queue->head++;
}

bool queue_empty(const Queue *queue)
{
    return queue->head == queue->size;
}
