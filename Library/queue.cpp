#include <stdlib.h>
#include "queue.h"

struct Queue
{
};

// создание пустой очереди
Queue *queue_create()
{
    return NULL;
}

// удаление очереди
void queue_delete(Queue *queue)
{
}

// включение элемента в очередь
void queue_insert(Queue *queue, int data)
{
}

// получение первого элемента очереди
int queue_get(Queue *queue)
{
    return 0;
}

// удаление первого элемента из очереди
void queue_remove(Queue *queue)
{
}

// проверка очереди на наличие элементов
bool queue_empty(Queue *queue)
{
    return true;
}
