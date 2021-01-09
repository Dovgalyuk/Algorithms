#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct Queue
{
	List* list;
	ListItem* lastItem;
};

Queue *queue_create()
{
	Queue* queue = new Queue;
	queue->list = list_create();
	queue->lastItem = NULL;
	return queue;
}

void queue_delete(Queue *queue)
{
	list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
	if (queue->lastItem)
	{
		queue->lastItem = list_insert_after(queue->list, queue->lastItem, data);
	}
	else
	{
		queue->lastItem = list_insert(queue->list, data);
	}
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
	list_erase(queue->list, list_first(queue->list));
	if (queue_empty(queue))
	{
		queue->lastItem = NULL;
	}
}

bool queue_empty(const Queue *queue)
{
    return (list_first(queue->list) == NULL) ? true : false;
}
