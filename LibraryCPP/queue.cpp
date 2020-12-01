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
	if ((queue->tail >= vector_size(queue->vector)) && (queue->head != 0))
		queue->tail = 1;
	else if (queue->tail + 1 == queue->head)
	{
		Vector* temp = vector_create();
		vector_resize(temp, 30);
		size_t i = 0;
		for (; i < queue->tail; i++)
			vector_set(temp, i, vector_get(queue->vector, i));
		queue->head++;
		i = queue->head;
		size_t lock_size = vector_size(queue->vector);
		for (; i <= lock_size; i++)
			vector_set(temp, i, vector_get(queue->vector, i - 1));
		vector_delete(queue->vector);
		queue->vector = temp;
	}
	else queue->tail++;
	vector_set(queue->vector, queue->tail - 1, data);
}

Data queue_get(const Queue* queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue* queue)
{
	if (queue->head + 1 == vector_size(queue->vector))
		queue->head = 0;
	else queue->head++;
}

bool queue_empty(const Queue* queue)
{
	if (queue->tail == queue->head)
		return true;
	else return false;
}