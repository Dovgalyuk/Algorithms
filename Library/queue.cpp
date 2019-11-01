#include <stdlib.h>
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
	Queue* a = new Queue;
	a->vector = vector_create();
	a->head = 0;
	a->tail = 0;
	return a;
}

void queue_delete(Queue* queue)
{
	vector_delete(queue->vector);
	delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	if (((((queue->tail) + 1) % vector_size(queue->vector) != queue->head)))
	{
		vector_set(queue->vector, queue->tail % vector_size(queue->vector), data);
		queue->tail += 1;
		if (queue->tail == vector_size(queue->vector)) queue->tail = 0;
	}
	else
	{
		if (queue->tail < queue->head)
		{
			Vector* tmp = vector_create();
			vector_resize(queue->vector, vector_size(queue->vector) * 2);
			int m = 0;
			for (int i = queue->head; i < vector_size(queue->vector); i++)
			{
				vector_set(tmp, m, vector_get(queue->vector, i));
				m += 1;
			}
			for (int i = 0; i < queue->tail; i++)
			{
				vector_set(tmp, m, vector_get(queue->vector, i));
				m += 1;
			}
			Vector* mp;
			mp = queue->vector;
			queue->vector = tmp;
			tmp = mp;
			queue->head = 0;
			queue->tail = m;
			vector_delete(tmp);
			vector_set(queue->vector, queue->tail % vector_size(queue->vector), data);
			queue->tail += 1;
		}
		else
			vector_resize(queue->vector, vector_size(queue->vector) * 2);
		vector_set(queue->vector, queue->tail % vector_size(queue->vector), data);
		queue->tail += 1;
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
		queue->head = 0;
	else queue->head += 1;
}

bool queue_empty(const Queue* queue)
{
	if (queue->head == queue->tail)
	{
		return true;
	}
	else return false;
}
