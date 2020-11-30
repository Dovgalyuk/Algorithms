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
	queue->head = queue->tail = 0;
	queue->vector = vector_create();
	vector_resize(queue->vector, 30);
	return queue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	if ((queue->tail >= vector_size(queue->vector)) && (queue->head != 0))
		queue->tail = 1;
	else queue->tail++;
	vector_set(queue->vector, queue->tail - 1, data);
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
	if (!queue_empty(queue))
	{
		vector_set(queue->vector, queue->head, NULL);
		if ((queue->head + 1 == queue->tail))
			queue->head = queue->tail = 0;
		else
			if (queue->head + 1 == vector_size(queue->vector))
				queue->head = 0;
			else queue->head++;
	}
}

bool queue_empty(const Queue* queue)
{
	if (queue->tail == queue->head)
		return true;
	else return false;
}