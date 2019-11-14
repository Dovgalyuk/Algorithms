#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct Queue
{
	List* head;
};

Queue* queue_create()
{
	Queue* temp = new Queue;
	temp->head = list_create();
	return temp;
}

void queue_delete(Queue* queue)
{
	list_delete(queue->head);
	delete queue;
}

void queue_insert(Queue* queue, Data data)
{
	list_insert(queue->head, data);
}

Data queue_get(const Queue* queue)
{
	return list_item_data(list_item_prev(list_first(queue->head)));
}

void queue_remove(Queue* queue)
{
	list_erase(queue->head, list_item_prev(list_first(queue->head)));
}

bool queue_empty(const Queue* queue)
{
	return (list_first(queue->head) == NULL);
}
