#include <cstddef>
#include "queue.h"
#include "list.h"

// Очередь на основе кольцевого списка:
// добавляем в конец списка, забираем из начала.
struct Queue
{
    List *list;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    // вставляем после последнего элемента, это O(1)
    // (если очередь пустая, list_last вернёт NULL и элемент встанет в начало)
    list_insert_after(queue->list, list_last(queue->list), data);
}

Data queue_get(const Queue *queue)
{
    return list_item_data(list_first(queue->list));
}

void queue_remove(Queue *queue)
{
    // удаляем первый элемент, это тоже O(1)
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    return list_first(queue->list) == NULL;
}
