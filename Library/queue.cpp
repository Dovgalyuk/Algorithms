#include <iostream>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* vector;
	size_t head;
	size_t tail;
};

Queue *queue_create()
{
	Queue* queue = new Queue;
	queue->vector = vector_create();
	queue->head = 0;
	queue->tail = 0;
	return queue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
	delete queue;
}

void queue_insert(Queue *queue, Data data)
{
	size_t size = vector_size(queue->vector);
	size_t rSize = queue->tail;

	if (size == 0)
	{
		queue->head = queue->tail;
		vector_resize(queue->vector, ++size);
	}
	else
	{
		if (size < rSize)
		{
			queue->tail++;
		}
		else if (size >= rSize)
		{
			vector_resize(queue->vector, ++size);
			queue->tail++;
		}
	}
	vector_set(queue->vector, queue->tail, data);
}

Data queue_get(const Queue *queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
	size_t size = vector_size(queue->vector);

	if (size == 1)
	{
		queue->tail = 0;
		queue->head = 0;
	}
	else if (size > 1)
	{
		queue->tail--;
		for (size_t i = 0; i < size; i++)
		{
			vector_set(queue->vector, i, vector_get(queue->vector, i + 1));
		}
	}
	vector_resize(queue->vector, --size);
}

bool queue_empty(const Queue *queue)
{
	return vector_size(queue->vector) == 0;
}