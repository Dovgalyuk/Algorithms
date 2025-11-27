#include "queue.h"
#include "list.h"

struct Queue {
    List *list;
};

Queue *queue_create() {
    Queue *queue = new Queue;
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue *queue) {
    list_delete(queue->list);
    delete queue;
}

void queue_insert(Queue *queue, Data data) {
    List *lst = queue->list;
    if (queue_empty(queue)) {
        list_insert(lst, data);  // Вставка в начало для пустого
    } else {
        list_insert_after(lst, lst->tail, data);  // Вставка после tail для конца
    }
}

Data queue_get(const Queue *queue) {
    ListItem *first = list_first(queue->list);
    return list_item_data(first);
}

void queue_remove(Queue *queue) {
    list_erase_first(queue->list);  // Удаление из начала
}

bool queue_empty(const Queue *queue) {
    return !list_first(queue->list);  // Пустой, если нет первого элемента
}

void queue_insert(Queue *queue, Data data) {
    list_insert_end(queue->list, data);  // Вставка в конец без знания tail
}