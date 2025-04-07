#include "queue.h"
#include <iostream>
#include <cstdlib>

using namespace std;

struct Queue {
    Vector *vector;
    size_t head; 
    size_t size;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->head = 0;
    queue->size = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    if (queue) {
        vector_delete(queue->vector);
        delete queue;
    }
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_size(queue->vector);
    if (queue->size == capacity) {

        size_t new_size = capacity == 0 ? 1 : capacity * 2;
        vector_resize(queue->vector, new_size);
        capacity = vector_size(queue->vector);
    }
    size_t insert_index = (queue->head + queue->size) % capacity;
    if (insert_index >= capacity){
        cerr << "index is out of bounds" << endl;
        exit(EXIT_FAILURE);
    }
    vector_resize(queue->vector, capacity);
    vector_set(queue->vector, insert_index, data);
    
    queue->size++;
}

Data queue_get(const Queue *queue)
{
    if (queue_empty(queue)) {
        cerr << "Error: Queue is empty\n";
        exit(EXIT_FAILURE);
    }
    return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) {
        cerr << "Error: Queue is empty\n";
        exit(EXIT_FAILURE);
    }

    queue->head = (queue->head + 1) % vector_size(queue->vector);
    queue->size--;
}

bool queue_empty(const Queue *queue)
{
    return queue->size == 0;
}
