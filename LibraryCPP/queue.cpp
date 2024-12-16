#include "queue.h"
#include <iostream>
#include "list.h"

struct Queue {
    List* list;
};

Queue* queue_create() {
    Queue* queue = new Queue();
    queue->list = list_create();
    return queue;
}

void queue_delete(Queue* queue) {
    if (queue) {
        list_delete(queue->list);
        delete queue;
    }
    else {
        std::cout << "Нет очереди1";
    }
}

void queue_insert(Queue* queue, Data data) {
    if (queue) {
        list_insert_end(queue->list, data);
    }
    else {
        std::cout <<"Нет очереди2";
    }
}

Data queue_get(const Queue* queue) {
    if (queue && queue->list) {
        if (!list_empty(queue->list)) {
            return list_item_data(list_first(queue->list));
        }
        else {
            std::cout <<"Очередь пуста1";
            return 0;
        }
    }
    std::cout <<"Нет очереди3";
    return 0;
}

void queue_remove(Queue* queue) {
    if (queue) {
        if (!list_empty(queue->list)) {
            list_erase_first(queue->list);
        }
        else {
            std::cout <<"Очередь пуста2";
        }
    }
    else {
        std::cout <<"Нет очереди4";
    }
}

bool queue_empty(const Queue* queue) {
    if (queue) {
        return list_empty(queue->list);
    }
    std::cout <<"Нет очереди5";
    return 1;
}
