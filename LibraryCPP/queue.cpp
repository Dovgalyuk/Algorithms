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
	size_t index = 0;
	if (queue->tail <= vector_size(queue->vector))
		index = queue->tail;
	else if (queue->tail - queue->head >= vector_size(queue->vector))
		index = queue->tail - queue->head;
	else if ((queue->tail > vector_size(queue->vector)) && (queue->head != 0))
	{
		if (queue->head < vector_size(queue->vector))
			index = queue->head;
		else if (queue->head > vector_size(queue->vector))
			if (queue->head % vector_size(queue->vector) != 0)
				index = queue->tail - queue->head;
	}
	
	vector_set(queue->vector, index, data);
	queue->tail++;
}

Data queue_get(const Queue* queue)
{
	size_t index = 0;
	if (queue->head != 0)
	{
		if (queue->head < vector_size(queue->vector))
			index = queue->head;
		else if (queue->head > vector_size(queue->vector))
			if (queue->head % vector_size(queue->vector) != 0)
				index = queue->head - vector_size(queue->vector);
	}
	return vector_get(queue->vector, index);
}

void queue_remove(Queue* queue)
{
	if (!queue_empty(queue))
	{
		if (queue->head + 1 == queue->tail)
		{
			queue->head = queue->tail = 0;
			vector_resize(queue->vector, 0);
			vector_resize(queue->vector, 30);
		}
		else
		{
			queue->head++;
			size_t index = 0;
			if (queue->head < vector_size(queue->vector))
				index = queue->head - 1;
			else if (queue->head > vector_size(queue->vector))
				if (queue->head % vector_size(queue->vector) != 0)
					index = queue->head - vector_size(queue->vector);
			vector_set(queue->vector, index, NULL);
		}
	}
}

bool queue_empty(const Queue* queue)
{
	if (queue->tail == queue->head)
		return true;
	else return false;
}