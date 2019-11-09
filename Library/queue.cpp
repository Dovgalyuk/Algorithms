#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* vector;
	size_t head, size;
};

Queue *queue_create()
{
	Queue* queue = new Queue;
	queue->vector = vector_create();
	queue->size = -1;
	queue->head = -1;
    return queue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
	delete[] queue;
}

void queue_insert(Queue* queue, Data data)
{
	size_t svector = vector_size(queue->vector);
	if ((queue->head == 0 && queue->size == svector - 1) || (queue->head == queue->size + 1))
	{
		Vector* n_vector = vector_create();
		vector_resize(n_vector, svector * 2);
		size_t i = 0;

		if (queue->head > queue->size)
		{
			for (size_t j = queue->head; j < svector; j++)
			{
				vector_set(n_vector, i, vector_get(queue->vector, j));
				i++;
			}
			for (size_t j = 0; j <= queue->size; j++)
			{
				vector_set(n_vector, i, vector_get(queue->vector, j));
				i++;
			}
		}
		else
		{
			for (size_t j = 0; j <= queue->size; j++)
			{
				vector_set(n_vector, i, vector_get(queue->vector, j));
				i++;
			}
		}
		vector_delete(queue->vector);
		queue->vector = n_vector;
		queue->head = 0;
		queue->size = i - 1;
		svector = vector_size(queue->vector);
	}
	if (queue->head == -1)
	{
		queue->head = 0;
	}
	queue->size = (queue->size + 1) % svector;
	vector_set(queue->vector, queue->size, data);
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
	if (queue->head == queue->size)
	{
		queue->head = -1;
		queue->size = -1;
	}
	else
	{
		queue->head = (queue->head + 1) % vector_size(queue->vector);
	}
}

bool queue_empty(const Queue *queue)
{
    return queue->head == -1;
}
