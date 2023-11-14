#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* data;  // ������������� ���������� "vector" ��� �������� ������
    size_t front;  // ������ ������ �������
    size_t rear;   // ������ ����� �������
    size_t capacity; // ����������� �������

    Queue(size_t cap = 10) : front(0), rear(0), capacity(cap + 1) {
        data = vector_create();
        vector_resize(data, capacity);
    }

    ~Queue() {
        vector_delete(data);
    }

    void queue_insert(Queue* queue, Data data) {
        if ((rear + 1) % capacity == front) {
            // ������� �����, ����� ��������� ������
            size_t newCapacity = capacity * 2;
            vector_resize(queue->data, newCapacity);
            if (front > rear) {
                // ���������� ����� ������ � ����� ������ ������
                for (size_t i = 0; i < front; ++i) {
                    vector_set(queue->data, i + capacity, vector_get(queue->data, i));
                }
                rear += capacity;
            }
            capacity = newCapacity;
        }
        vector_set(queue->data, rear, data);
        rear = (rear + 1) % capacity;
    }

    Data queue_get(const Queue* queue) {
        if (!queue_empty(queue)) {
            Data value = vector_get(queue->data, front);
            front = (front + 1) % capacity;
            return value;
        }
        else {
            // ���������� �����-�� ��������� Data � ������ ������ �������
            return (Data)0;
        }
    }

    void queue_remove(Queue* queue) {
        if (!queue_empty(queue)) {
            front = (front + 1) % capacity;
        }
    }

    bool queue_empty(const Queue* queue) {
        return front == rear;
    }
};