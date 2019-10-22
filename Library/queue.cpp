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
	size_t size = queue->tail > queue->head ? queue->tail - queue->head + 1 : vector_size(queue->vector) - queue->head + queue->tail;
	size_t next = size > 0 ? (queue->tail + 1) % size : 0;
	size_t vSize = vector_size(queue->vector);

	if (next == queue->head)
	{
		Vector* temp = vector_create();
		vector_resize(temp, size);
		int ord = 0;

		for (size_t i = queue->head; i < vSize; i++)
		{

			vector_set(temp, ord, vector_get(queue->vector, i));
			ord++;
		}

		queue->head = 0;

		for (size_t i = 0; i < queue->tail; i++)
		{
			vector_set(temp, ord, vector_get(queue->vector, i));
			ord++;
		}

		vector_set(temp, ord, data);
		vector_delete(queue->vector);
		queue->vector = temp; 
		queue->tail = size;
	}
	else
	{
		queue->tail++;
		vector_set(queue->vector, queue->tail, data);
	}
	vector_set(queue->vector, queue->tail, data);
}

Data queue_get(const Queue *queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
	if (queue->tail == queue->head - 1)
	{
		queue->head = 0;
	}
	else
	{
		queue->head++;
	}
}

bool queue_empty(const Queue *queue)
{
	return queue->head - 1 == queue->tail;
}