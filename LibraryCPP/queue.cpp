#include "queue.h"

struct Queue
{
	size_t head;
	size_t tail;
	Vector* vector;
};

Queue* queue_create()
{
	Queue* queue = new Queue;
	queue->head = 0;
	queue->tail = 0;
	queue->vector = vector_create();

	return queue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	vector_set(queue->vector, queue->tail, data);
	queue->tail++;
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
	if (!queue_empty(queue))
	{
		if (queue->tail == 1)
			queue->tail = 0;
		else
			queue->tail -= 1;

		vector_resize(queue->vector, queue->tail);
	}
}

bool queue_empty(const Queue* queue)
{
	if (queue->tail == queue->head)
		return true;
	else
		return false;
}