#include <stdlib.h>
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
	vector_resize(queue->vector, 50);
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
	if (queue->tail == vector_size(queue->vector) - 1 && queue->head == 0)
	{
		vector_resize(queue->vector, vector_size(queue->vector) * 2);
		vector_set(queue->vector, queue->tail, data);
		queue->tail++;
	}
	else if (queue->tail + 1 == queue->head)
	{
		size_t temp = 0;
		Vector* vector = vector_create();
		vector_resize(vector, vector_size(queue->vector) * 2);
		
		for (int i = queue->head; i < vector_size(queue->vector); i++)
		{
			vector_set(vector, temp, vector_get(queue->vector, i));
			temp++;
		}

		for (int i = 0; i < queue->tail; i++)
		{
			vector_set(vector, temp, vector_get(queue->vector, i));
			temp++;
		}

		vector_delete(queue->vector);
		queue->vector = vector;

		queue->head = 0;
		queue->tail = temp;

		vector_set(queue->vector, queue->tail, data);
		queue->tail++;
	}
	else
	{
		vector_set(queue->vector, queue->tail, data);
		if (queue->tail == vector_size(queue->vector) - 1)
			queue->tail = 0;
		else
			queue->tail++;
	}
}	

Data queue_get(const Queue *queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
	if (queue->head == vector_size(queue->vector) - 1)
		queue->head = 0;
	else
		queue->head++;
}

bool queue_empty(const Queue *queue)
{
	return queue->head == queue->tail;
}
