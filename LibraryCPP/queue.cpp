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
	if (queue->tail < vector_size(queue->vector) - 1)
	{
		vector_set(queue->vector, queue->tail, data);
		queue->tail++;
	}
	else
	{
		if (queue->head != 0)
		{
			for (int i = queue->head; i < queue->tail; i++)
				vector_set(queue->vector, i - queue->head, vector_get(queue->vector, i));
			queue->tail -= queue->head;
			queue->head = 0;
		}
		else
			vector_resize(queue->vector, vector_size(queue->vector) + queue->tail);
		
		vector_set(queue->vector, queue->tail, data);
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
