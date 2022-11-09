#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    int head;
    int rear;

    Queue() {
        vector = vector_create();
        vector_resize(vector, 20);
        head = -1;
        rear = -1;
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
        queue->rear = 0;
        queue->head = 0;
    } else if (queue->rear % size == queue->head) {
        throw "Error: Queue is full!";
    }

    int rear = queue->rear % size;
    // if(rear == size - 1)

    // if(rear == size - 1) {
    //     vector_resize(queue->vector, size*2);

    vector_set(queue->vector, rear, data);
    queue->rear = rear+1;
}

Data queue_get(const Queue *queue)
{
    if(!queue_empty(queue)) {
        Data value = vector_get(queue->vector, queue->head);
        return value;
    }
    return Data();
}

void queue_remove(Queue *queue)
{   
    size_t size = vector_size(queue->vector);
    int head = queue->head;

    if(!queue_empty(queue)) {
        head++;

        if(queue->rear == head) {
            queue->head = -1;
            queue->rear = -1;
        } else {
            queue->head = head % size;
        }
    }
}

bool queue_empty(const Queue *queue)
{
    return (queue->rear == -1 && queue->head == -1);
}