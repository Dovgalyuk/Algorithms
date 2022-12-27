#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    int first;
    int last;

    Queue() {
        vector = vector_create();
        vector_resize(vector, 100);
        first = -1;
        last = -1;
    }

    ~Queue() {
        vector_delete(vector);
    }
};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t size = vector_size(queue->vector);

    if(queue_empty(queue)) {
        queue->first = 0;
        queue->last = 0;
    } else if (queue->last % size == queue->first) {
        Vector *incresedVector = vector_create();
        vector_resize(incresedVector, size * 2);

        int counter = 0;

        for(int i = queue->first; i < size; i++) {

            vector_set(
                    incresedVector,
                    counter,
                    vector_get(queue->vector,i)
            );
            counter++;
        }
        for(int i = 0; i < queue->last; i++) {
            vector_set(incresedVector, counter, vector_get(queue->vector,i));
            counter++;
        }
        vector_delete(queue->vector);
        queue->vector = incresedVector;
        queue->first = 0;
        queue->last = size;

        size = vector_size(queue->vector);
    }

    int last = queue->last % size;

    vector_set(queue->vector, last, data);
    queue->last = last+1;
}

Data queue_get(const Queue *queue)
{
    if (!queue_empty(queue)) {
        Data item = vector_get(queue->vector, queue->first);
        return item;
    }
}

void queue_remove(Queue *queue)
{
    if (queue->first + 1 == vector_size(queue->vector))
        queue->first = 0;
    else queue->first++;
}

bool queue_empty(const Queue *queue)
{
    return queue->last == queue->first;
}