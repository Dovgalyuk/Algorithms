#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector* Data;
	size_t start, end;
};

Queue* queue_create()
{
	Queue* temp = new Queue;
	temp->Data = vector_create();
	vector_resize(temp->Data, 2);
	temp->start = temp->end = 0;
	return temp;
}

void queue_delete(Queue* queue)
{
	vector_delete(queue->Data);
	delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	if (queue->start == 0 && queue->end + 1 == vector_size(queue->Data))
	{
		vector_resize(queue->Data, vector_size(queue->Data) * 2);
	}
	else
		if (queue->end + 1 == queue->start)
		{
			Vector* temp = vector_create();
			vector_resize(temp, vector_size(queue->Data) * 2);
			for (size_t i = queue->start; i < vector_size(queue->Data); i++)
				vector_set(temp, i - queue->start, vector_get(queue->Data, i));
			for (size_t i = 0; i < queue->end; i++)
				vector_set(temp, i + (vector_size(queue->Data) - queue->start), vector_get(queue->Data, i));
			vector_delete(queue->Data);
			queue->Data = temp;
			queue->end = vector_size(temp) / 2 - 1;
			queue->start = 0;
		}
	vector_set(queue->Data, queue->end, data);
	if (queue->end + 1 >= vector_size(queue->Data))
		queue->end = 0;
	else
		queue->end++;
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->Data, queue->start);
}

void queue_remove(Queue* queue)
{
	if (queue->start + 1 < vector_size(queue->Data))
		queue->start++;
	else
		queue->start = 0;
}

bool queue_empty(const Queue* queue)
{
	return queue->end == queue->start;
}
