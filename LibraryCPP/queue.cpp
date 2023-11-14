#include "queue.h"
#include "vector.h"

struct Queue {
    Vector* data;  // Использование библиотеки "vector" для хранения данных
    size_t front;  // Индекс начала очереди
    size_t rear;   // Индекс конца очереди
    size_t capacity; // Вместимость очереди

    Queue(size_t cap = 10) : front(0), rear(0), capacity(cap + 1) {
        data = vector_create();
        vector_resize(data, capacity);
    }

    ~Queue() {
        vector_delete(data);
    }

    void queue_insert(Queue* queue, Data data) {
        if ((rear + 1) % capacity == front) {
            // Очередь полна, нужно увеличить размер
            size_t newCapacity = capacity * 2;
            vector_resize(queue->data, newCapacity);
            if (front > rear) {
                // Перемещаем часть данных в конец нового буфера
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
            // Возвращаем какую-то дефолтную Data в случае пустой очереди
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