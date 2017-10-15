#include <stdlib.h>
#include "queue.h"
#include "list.h"

struct Queue
{
	List * list;
};

// �������� ������ �������
Queue *queue_create()
{
	Queue * newQue = new Queue;
	newQue->list = list_create();
    return newQue;
}

// �������� �������
void queue_delete(Queue *queue)
{
	delete queue;
}

// ��������� �������� � �������
void queue_insert(Queue *queue, int data)
{
	list_insert(queue->list, data);
}

// ��������� ������� �������� �������
int queue_get(Queue *queue)
{
	return list_item_data(list_first(queue->list));
}

// �������� ������� �������� �� �������
void queue_remove(Queue *queue)
{
	list_erase(queue->list,list_first(queue->list));
}

// �������� ������� �� ������� ���������
bool queue_empty(Queue *queue)
{
	if (list_item_data(list_first(queue->list)))
		return false;
	else
		return true;
}
