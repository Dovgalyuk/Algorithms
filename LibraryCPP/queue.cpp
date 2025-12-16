#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* data;   // кольцевой буфер
    size_t front;   // индекс первого элемента
    size_t count;   // количество элементов
};

Queue* queue_create() {
    Queue* queue = new Queue;
    queue->data = vector_create();
    queue->front = 0;
    queue->count = 0;
    vector_resize(queue->data, 4);
    return queue;
}

void queue_delete(Queue* queue) {
    vector_delete(queue->data);
    delete queue;
}

bool queue_empty(const Queue* queue) {
    return queue->count == 0;
}

void queue_insert(Queue* queue, Data data) {
    size_t capacity = vector_size(queue->data);
    
    if (queue->count == capacity) {
        size_t new_capacity = capacity * 2;
        Vector* new_data = vector_create();
        vector_resize(new_data, new_capacity);
        
        for (size_t i = 0; i < queue->count; ++i) {
            size_t old_index = (queue->front + i) % capacity;
            vector_set(new_data, i, vector_get(queue->data, old_index));
        }
        
        vector_delete(queue->data);
        queue->data = new_data;
        queue->front = 0;
        capacity = new_capacity;
    }
    
    size_t insert_pos = (queue->front + queue->count) % capacity;
    vector_set(queue->data, insert_pos, data);
    queue->count++;
}

Data queue_get(const Queue* queue) {
    return queue_empty(queue) ? (Data)0 : vector_get(queue->data, queue->front);
}

void queue_remove(Queue* queue) {
    if (!queue_empty(queue)) {
        queue->front = (queue->front + 1) % vector_size(queue->data);
        queue->count--;
    }
}
