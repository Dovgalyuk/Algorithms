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
    size_t current_size = vector_size(queue->vector);

    if (current_size == 0) {
        vector_resize(queue->vector, 1);
        vector_set(queue->vector, 0, data);
        queue->front = 0;
        queue->rear = 1;
        return;
    }

    if (queue->front == (queue->rear + 1) % current_size) {
        size_t new_size = current_size * 2;
        Vector* resized_vector = vector_create();
        vector_resize(resized_vector, new_size);

        size_t j = 0;
        for (size_t i = queue->front; i != queue->rear; i = (i + 1) % current_size) {
            vector_set(resized_vector, j++, vector_get(queue->vector, i));
        }

        vector_delete(queue->vector);
        queue->vector = resized_vector;
        queue->front = 0;
        queue->rear = current_size;

        current_size = new_size;
    }

    vector_set(queue->vector, queue->rear, data);
    queue->rear = (queue->rear + 1) % current_size;
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