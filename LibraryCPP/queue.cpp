#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector* vector;
    size_t head;
    size_t tail;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    vector_resize(queue->vector, 100);
    queue->head = 0;
    queue->tail = 0;
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    Vector* que_vector = queue->vector;
    if (queue->tail >= vector_size(queue->vector) - 1 && queue->head == 0) {
        vector_resize(que_vector, vector_size(queue->vector) * 2);
    }
    else if (queue->tail + 1 == queue->head) {
        Vector* new_vector = vector_create();
        vector_resize(new_vector, vector_size(que_vector) * 2);
        size_t j = 0;
        for (int i = queue->head; i < vector_size(que_vector); i++) {
            vector_set(new_vector, j, vector_get(que_vector, i));
            j++;
        }
        for (int i = 0; i <= queue->tail; i++) {
            vector_set(new_vector, j, vector_get(que_vector, i));
            j++;
        }
        queue->vector = new_vector;
        vector_delete(que_vector);
        queue->head = 0;
        queue->tail = j + 1;
    }
}

Data queue_get(const Queue *queue)
{
    if (!queue_empty(queue)) {
        return vector_get(queue->vector, queue->head);
    }
    else {
        return 0;
    }
}

void queue_remove(Queue *queue)
{
    if (!queue_empty(queue)) {
        if (queue->head >= vector_size(queue->vector) - 1) {
            queue->head = 0;
        }
        else {
            queue->head++;
        }
    }
}   

bool queue_empty(const Queue *queue)
{
    return queue->tail == queue->head;
}
