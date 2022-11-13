#include "queue.h"
#include "vector.h"

struct Queue
{
    Vector *vector;
    int head;
    int rear;

    Queue() {
        vector = vector_create();
        vector_resize(vector, 2);
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
        Data *buff = new Data[size*2];
        int counter = 0;

        for(int i = queue->head; i < size; i++) {
            buff[counter] = vector_get(queue->vector,i);  
            counter++;
        }
        for(int i = 0; i < queue->rear; i++) {
            buff[counter] = vector_get(queue->vector,i);
            counter++;
        }
        queue->head = 0;
        queue->rear = size;

        for(int i = 0; i < size; i++) {
            vector_set(queue->vector, i, buff[i]);
        }
        vector_resize(queue->vector, size*2);
        size = vector_size(queue->vector);
        delete[] buff;
    }

    int rear = queue->rear % size;

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