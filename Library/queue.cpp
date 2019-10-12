#include <stdlib.h>
#include "queue.h"
#include "vector.h"

struct Queue
{
	Vector *cont;
	size_t size, first;
};

Queue *queue_create()
{
	Queue* temp = new Queue;
	temp->cont = vector_create();
	temp->size = 0;
	temp->first = 0;
	return temp;;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->cont);
	delete queue;
}

void queue_insert(Queue *queue, Data data)
{
	vector_set(queue->cont, queue->size, data);
	queue->size++;
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->cont, queue->first);
}

void queue_remove(Queue *queue)
{
	queue->first++;
}

bool queue_empty(const Queue *queue)
{
    return queue->size==queue->first;
}
