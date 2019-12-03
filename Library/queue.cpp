#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct Queue
{
	List* data; 
	ListItem* last; 
};

Queue* queue_create()
{
	Queue* p = new Queue; 
	p->data = list_create(); 
	return p; 
}

void queue_delete(Queue* queue)
{
	list_delete(queue->data);
	delete queue; 
}

void queue_insert(Queue* queue, Data data)
{
	if (!list_first(queue->data)) 
		queue->last = list_insert(queue->data, data); 
	else
		queue->last = list_insert_after(queue->data, queue->last, data); 
}

Data queue_get(const Queue* queue)
{
	return list_item_data(list_first(queue->data)); 
}

void queue_remove(Queue* queue)
{
	list_erase_first(queue->data); 
}

bool queue_empty(const Queue* queue)
{
	return !list_first(queue->data); 
}
