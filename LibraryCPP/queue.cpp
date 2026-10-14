#include "queue.h"
#include "list.h"

struct Queue {
    List* list;
};

Queue* queue_create() {
    Queue* q = new Queue;
    q->list = list_create();
    return q;
}

void queue_delete(Queue* q) {
    list_delete(q->list);
    delete q;
}

void queue_insert(Queue* q, Data data) {
    ListItem* last = list_last(q->list);
    if (!last) list_insert(q->list, data);
    else list_insert_after(q->list, last, data);
}

Data queue_get(const Queue* q) {
    ListItem* first = list_first(const_cast<List*>(q->list));
    return first ? list_item_data(first) : 0;
}

void queue_remove(Queue* q) {
    list_erase_first(q->list);
}

bool queue_empty(const Queue* q) {
    return list_first(const_cast<List*>(q->list)) == nullptr;
}
