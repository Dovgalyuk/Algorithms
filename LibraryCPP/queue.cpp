#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* vector;
    size_t front; // ������ ������ �������
    size_t rear; // ������ ����� �������

    Queue() {
        vector = vector_create();
        front = 0;
        rear = 0;
    }

    ~Queue() {
        vector_delete(vector);
    }
};

Queue* queue_create() {
    return new Queue;
}

void queue_delete(Queue* queue) {
    delete queue;
}

void queue_insert(Queue* queue, Data data) {
    vector_resize(queue->vector, queue->rear + 1); // ����������� ������ ������� ��� ������� ��������
    vector_set(queue->vector, queue->rear, data);
    queue->rear++;
}

Data queue_get(const Queue* queue) {
    if (queue->front == queue->rear) {
        return (Data)0; // ���� ������� �����, ���������� �������� �� ��������� 
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue* queue) {
    if (queue->front == queue->rear) {
        return; // ������ �������, ���� ������� �����
    }
    queue->front++;

    // ���� ������ ������� �������� ����� �������, �������� � ������
    if (queue->front == queue->rear) {
        queue->front = 0;
        queue->rear = 0;
    }
}

bool queue_empty(const Queue* queue) {
    return queue->front == queue->rear;
}