#include "queue.h"

struct Queue
{
    Vector* data;  // кольцевой буфер на основе vector
    size_t front;  // индекс начала очереди
    size_t back;   // индекс следующего свободного места
    size_t count;  // количество элементов в очереди
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->data = vector_create();
    queue->front = 0;
    queue->back = 0;
    queue->count = 0;
    vector_resize(queue->data, 4); // начальная емкость
    return queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->data);
    delete queue;
}

bool queue_empty(const Queue* queue)
{
    return queue->count == 0;
}

size_t queue_size(const Queue* queue)
{
    return queue->count;
}

void queue_insert(Queue* queue, Data data)
{
    // Если буфер полный, увеличиваем его
    if (queue->count == vector_size(queue->data)) {
        size_t old_capacity = vector_size(queue->data);
        size_t new_capacity = old_capacity * 2;
        vector_resize(queue->data, new_capacity);
        
        // Если очередь "обернулась", нужно перераспределить элементы
        if (queue->back <= queue->front && queue->count > 0) {
            // Копируем элементы от front до конца старого массива
            // в конец нового массива
            for (size_t i = 0; i < old_capacity - queue->front; ++i) {
                vector_set(queue->data, new_capacity - i - 1, 
                          vector_get(queue->data, old_capacity - i - 1));
            }
            queue->front = new_capacity - (old_capacity - queue->front);
        }
    }
    
    // Вставляем элемент
    vector_set(queue->data, queue->back, data);
    queue->back = (queue->back + 1) % vector_size(queue->data);
    queue->count++;
}

Data queue_get(const Queue* queue)
{
    if (queue_empty(queue)) {
        return (Data)0;
    }
    return vector_get(queue->data, queue->front);
}

void queue_remove(Queue* queue)
{
    if (queue_empty(queue)) {
        return;
    }
    queue->front = (queue->front + 1) % vector_size(queue->data);
    queue->count--;
}
