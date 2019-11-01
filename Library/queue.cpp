#include <iostream>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* vector;
	size_t head;
	size_t tail;
};

Queue* queue_create()
{
	Queue* queue = new Queue;
	queue->vector = vector_create();
	queue->head = 0;
	queue->tail = 0;
	return queue;
}

void queue_delete(Queue* queue)
{
	vector_delete(queue->vector);
	delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	size_t vSize = vector_size(queue->vector);
	size_t next = (queue->tail + 1) % vSize;

	if (next == queue->head)
	{
		if (queue->tail < queue->head)
		{
			Vector* temp = vector_create();
			vector_resize(queue->vector, vSize * 2);
			size_t ord = 0;

			for (size_t i = queue->head; i < vSize; i++)
			{
				vector_set(temp, ord, vector_get(queue->vector, i));
				ord++;
			}
			for (size_t i = 0; i < queue->tail; i++)
			{
				vector_set(temp, ord, vector_get(queue->vector, i));
				ord++;
			}

			queue->vector = temp;
			queue->head = 0;
			queue->tail = ord;
			vector_delete(temp);
			vector_set(queue->vector, queue->tail, data);
			queue->tail++;
		}
		else
		{
			vector_resize(queue->vector, vSize * 2);
		}
		vector_set(queue->vector, queue->tail, data);
		queue->tail++;
	}
	else
	{
		vector_set(queue->vector, queue->tail, data);
		queue->tail++;
	}
	queue->tail = queue->tail % vector_size(queue->vector);
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
	if (queue->head == vector_size(queue->vector) - 1)
	{
		queue->head = 0;
	}
	else
	{
		queue->head++;
	}
}

bool queue_empty(const Queue* queue)
{
	return queue->head == queue->tail;
}