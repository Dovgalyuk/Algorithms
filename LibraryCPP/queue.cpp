#include "queue.h"
#include "list.h"

struct Queue
{
    List* list;
    ListItem* tail;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->list = list_create();
    queue->tail = nullptr;
    return queue;
}

void queue_delete(Queue *queue)
{
    if (queue) {
        list_delete(queue->list);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    if (!queue) return;
    
    if (queue_empty(queue)) {
        // Очередь пуста - вставляем первый элемент
        list_insert(queue->list, data);
        queue->tail = list_first(queue->list);
    } else {
        // Добавляем в конец и обновляем tail
        list_insert_after(queue->list, queue->tail, data);
        queue->tail = list_item_next(queue->tail);
    }
}

Data queue_get(const Queue *queue)
{
    if (queue && list_first(queue->list)) {
        return list_item_data(list_first(queue->list));
    }
    return Data(0);
}

void queue_remove(Queue *queue)
{
    if (!queue) return;
    
    // Если удаляем единственный элемент, сбрасываем tail
    if (list_first(queue->list) == queue->tail) {
        queue->tail = nullptr;
    }
    
    list_erase_first(queue->list);
}

bool queue_empty(const Queue *queue)
{
    return !queue || list_first(queue->list) == nullptr;
}