#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* vec;
	size_t head, tail;
};

Queue* queue_create()
{
	Queue* q = new Queue;
	q->vec = vector_create();
	q->head = q->tail = 0;
	q->tail = 0;
	return q;
}

void queue_delete(Queue* queue)
{
	vector_delete(queue->vec);
	delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	if (queue->head == 0 && queue->tail + 1 == vector_size(queue->vec))
	{
		vector_resize(queue->vec, vector_size(queue->vec) * 2);
	}
	else
		if (queue->tail + 1 == queue->head)
		{
			Vector* t = vector_create();
			vector_resize(t, vector_size(queue->vec) * 2);
			for (size_t i = queue->head; i < vector_size(queue->vec); i++)
				vector_set(t, i - queue->head, vector_get(queue->vec, i));
			for (size_t i = 0; i < queue->tail; i++)
				vector_set(t, i + (vector_size(queue->vec) - queue->head), vector_get(queue->vec, i));
			vector_delete(queue->vec);
			queue->vec = t;
			queue->tail = vector_size(t) / 2 - 1;
			queue->head = 0;
		}
	vector_set(queue->vec, queue->tail, data);
	if (queue->tail + 1 >= vector_size(queue->vec))
		queue->tail = 0;
	else
		queue->tail++;
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->vec, queue->head);
}

void queue_remove(Queue* queue)
{
	if (queue->head == vector_size(queue->vec) - 1)
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