#include <stdlib.h>
#include "queue.h"
#include "list.h"

typedef struct Queue
{
	List* list;
	
} Queue;

Queue* queue_create(ffree f)
{
	Queue* newqueue = (Queue*)malloc(sizeof(Queue));
	newqueue->list = list_create(f);
	return newqueue;
}

void queue_delete(Queue* queue)
{
	list_delete(queue->list);
	free(queue);
}

void queue_insert(Queue* queue, Data data)
{
	if (list_first(queue->list) == NULL)
	{
		list_insert(queue->list, data);
		return;
	}
	list_insert_after(queue->list, list_first(queue->list), data);
}

Data queue_get(const Queue* queue)
{
	if (!queue_empty(queue)) {
		return list_item_data(list_first(queue->list));
	}
	return (Data)0;
}

void queue_remove(Queue* queue)
{
	if (!queue_empty(queue))
		list_erase_first(queue->list);
}

bool queue_empty(const Queue* queue)
{
	return list_first(queue->list) == NULL;
}
