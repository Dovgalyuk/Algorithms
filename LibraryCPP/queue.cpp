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
        if (queue->head != 0) {
            
            Vector* new_vector = vector_create();
            vector_resize(new_vector, new_size);

            for (size_t i = 0; i < queue->size; ++i) {
                Data elem = vector_get(queue->vector, (queue->head + i) % capacity);
                vector_set(new_vector, i, elem);
            }
            
            vector_set(new_vector, queue->size, data);
            vector_delete(queue->vector); 
            queue->vector = new_vector; 
            queue->head = 0;
            queue->size++; 
        }
        else
        {
            vector_resize(queue->vector, new_size);
        }
        capacity = vector_size(queue->vector);
    }
    if (capacity==0){
        vector_resize(queue->vector, 1);
        capacity = vector_size(queue->vector);
    }
    size_t insert_index = (queue->head + queue->size) % capacity;
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
