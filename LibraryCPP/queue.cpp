#include <cstddef>
#include "queue.h"
#include "list.h"

struct Queue
{
    List *list;
    ListItem *tail; // Указатель на хвост для реализации O(1) вставки
};

// Create empty queue
Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->list = list_create();
    queue->tail = NULL;
    return queue;
}

// Deletes queue
void queue_delete(Queue *queue)
{
    if (queue)
    {
        list_delete(queue->list);
        delete queue;
    }
}

// Includes new element into the queue
// Should be O(1) on average
void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;

    if (queue_empty(queue))
    {
        // Если очередь пуста, вставляем в начало списка
        ListItem *item = list_insert(queue->list, data);
        queue->tail = item;
    }
    else
    {
        // Вставляем после текущего хвоста в O(1)
        queue->tail = list_insert_after(queue->list, queue->tail, data);
    }
}

// Retrieves first element from the queue
Data queue_get(const Queue *queue)
{
    if (!queue || queue_empty(queue))
    {
        return (Data)0;
    }
    ListItem *first = list_first(queue->list);
    return list_item_data(first);
}

// Removes first element from the queue
// Should be O(1) on average
void queue_remove(Queue *queue)
{
    if (!queue || queue_empty(queue)) return;

    ListItem *first = list_first(queue->list);
    if (first == queue->tail)
    {
        // Если удаляем единственный элемент, хвост тоже сбрасывается
        queue->tail = NULL;
    }
    list_erase_first(queue->list);
}

// Returns true if the queue is empty
bool queue_empty(const Queue *queue)
{
    if (!queue) return true;
    return list_first(queue->list) == NULL;
}
