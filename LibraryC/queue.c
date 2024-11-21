#include <stdlib.h>

#include "queue.h"

typedef struct Queue {
    List *list;
    FFree *destruct;
} Queue;

Queue *queue_create(FFree f) {
    Queue* new_queue = malloc(sizeof(Queue));
    new_queue -> list = list_create(f);
    new_queue -> destruct = f;
    return new_queue;
}

void queue_delete(Queue *queue) {
    list_delete(queue -> list);
    free(queue);
}

void queue_insert(Queue *queue, Data data) {
    if (!queue_empty(queue)) {
        list_insert_after(queue -> list, list_item_prev(list_first(queue -> list)), data);
    } else{
        list_insert(queue -> list, data);
    }
}

Data queue_get(const Queue *queue) {
    return list_item_data(list_first(queue -> list));
}

void queue_remove(Queue *queue) {
    list_erase_first(queue -> list);
}

bool queue_empty(const Queue *queue) {
    return list_first(queue -> list) ? false : true;
}
