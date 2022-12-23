#include "queue.h"
#include "vector.h"
#include <iostream>

using namespace std;

struct Queue
{
    Vector* vector;

    size_t head;
    size_t tail;

    Queue() {
        this->vector = vector_create();
        this->head = NULL;
        this->tail = NULL;
    }

    ~Queue() {
        vector_delete(this->vector);
    }

};

Queue *queue_create()
{
    return new Queue;
}

void queue_delete(Queue *queue)
{
    // TODO: free queue items
    delete queue;
}

void queue_insert(Queue *queue, Data data)//Добавление нового элемента в очереди
{
    if (queue_empty(queue)) { 
        vector_resize(queue->vector, 20);
        vector_set(queue->vector, queue->head, data);
        queue->tail++;
    }
    else if (queue->tail == vector_size(queue->vector) - 1 && queue->head == 0) {
        vector_resize(queue->vector, vector_size(queue->vector) * 2);
        vector_set(queue->vector, queue->tail, data);
        queue->tail++;
    }
    else if (queue->tail + 1 == queue->head) {
        Vector* temp = vector_create();
        vector_resize(temp, vector_size(queue->vector)*2);

        int temp_index = 0;

        for (size_t i = queue->head; i < vector_size(queue->vector); i++) 
        {
            vector_set(temp, temp_index, vector_get(queue->vector, i));
            temp_index++;
        }

        for (size_t i = 0; i < queue->tail; i++)
        {
            vector_set(temp, temp_index, vector_get(queue->vector, i));
            temp_index++;
        }

        vector_delete(queue->vector);
        queue->vector = temp;

        queue->head = 0;
        queue->tail = temp_index;
    }
    else if (queue->tail == vector_size(queue->vector) - 1 && queue->head >= 0) {
        vector_set(queue->vector, queue->tail, data);
        queue->tail = 0;
    }
    else {
        vector_set(queue->vector, queue->tail, data);
        queue->tail++;
    }
}

Data queue_get(const Queue *queue)
{
    return vector_get(queue->vector,queue->head);
}

void queue_remove(Queue *queue)
{
    if (queue_empty(queue)) cout<<"Очередь пуста";
    else if (queue->head == vector_size(queue->vector) - 1) {
        vector_set(queue->vector, queue->head, 0);
        queue->head = 0;
    }
    else {
        vector_set(queue->vector, queue->head, 0);
        queue->head++;
    }
}

bool queue_empty(const Queue *queue)
{
    if (queue->head == queue->tail) return true;
    else return false;
}
