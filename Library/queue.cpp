#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct Queue
{
	List * list;
};

// создание пустой очереди
Queue *queue_create()
{
	Queue * newQue = new Queue;
	newQue->list = list_create();
    return newQue;
}

// удаление очереди
void queue_delete(Queue *queue)
{
	delete queue;
}

// включение элемента в очередь
void queue_insert(Queue *queue, int data)
{
	list_insert(queue->list, data);
}

// получение первого элемента очереди
int queue_get(Queue *queue)
{
	return list_item_data(list_first(queue->list));
}

// удаление первого элемента из очереди
void queue_remove(Queue *queue)
{
	list_erase(queue->list,list_first(queue->list));
}

// проверка очереди на наличие элементов
bool queue_empty(Queue *queue)
{
	if (list_item_data(list_first(queue->list)))
		return false;
	else
		return true;
}
