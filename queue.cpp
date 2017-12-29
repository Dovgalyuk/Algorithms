#include <stdlib.h>
#include "queue.h"
#include "vector.h"
#include "iostream"

using namespace std;

struct Queue
{
    Vector *vector;
    int front,
    rear;
};

Queue *queue_create()
{
    Queue* queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->rear = 0;
    
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}


void queue_insert(Queue *queue, int data) {
    size_t size = vector_size(queue->vector);
 
    if (size == 0) {
        vector_resize(queue->vector, ++size); // resizes it to 1
        vector_set(queue->vector, queue->front, data); // adds data to front
        queue->front = queue->rear; // makes front point to rear
    } else
    {
        vector_resize(queue->vector, ++size); // resizes it to 1
        queue->rear = size - 1; // faz o ponteiro rear andar sempre para a casa seguinte, sem pular casas. OBS: fazer breakdown na função caso não perceber
        vector_set(queue->vector, queue->rear, data);
    }
    
}

int queue_get(Queue *queue)
{
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    size_t size = vector_size(queue->vector);
    
    if(size == 1){
        queue->rear = queue->front;
        
    }
    else if (size > 1) {
        // shifts every element on position down [0,1,2,3] -> [1,2,3](size-1)
        for (int i = 0; i < size - 1; i++) {
            vector_set(queue->vector, i, vector_get(queue->vector, i + 1));// apaga dessa forma a primeira posição do queue
        }
    }
    vector_resize(queue->vector, size-1); //refaz o tamanho do vector
}

bool queue_empty(Queue *queue)
{
    if ( vector_size(queue->vector) == 0 ) {
        return true; //vazio
    }else {
        return false; // não vazio
    }
}

