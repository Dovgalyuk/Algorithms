#include "queue.h"
#include "vector.h"
#include <cstddef>

struct Queue
{
    Vector *vector;
    size_t front;
    size_t count;
};

Queue *queue_create()
{
    Queue *queue = new Queue;
    queue->vector = vector_create();
    queue->front = 0;
    queue->count = 0;
    // Инициализируем очередь с начальной ёмкостью
    vector_resize(queue->vector, 4);
    return queue;
}

void queue_delete(Queue *queue)
{
    vector_delete(queue->vector);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    size_t capacity = vector_size(queue->vector);
    
    // Если очередь заполнена, расширяем её
    if (queue->count >= capacity)
    {
        // Создаём новый вектор с удвоенной ёмкостью
        Vector *new_vector = vector_create();
        vector_resize(new_vector, capacity * 2);
        
        // Копируем элементы из старого вектора в новый в правильном порядке
        for (size_t i = 0; i < queue->count; ++i)
        {
            size_t idx = (queue->front + i) % capacity;
            vector_set(new_vector, i, vector_get(queue->vector, idx));
        }
        
        // Удаляем старый вектор и обновляем указатели
        vector_delete(queue->vector);
        queue->vector = new_vector;
        queue->front = 0;
        capacity = capacity * 2;
    }
    
    // Вычисляем позицию для вставки: back = (front + count) % capacity
    size_t back = (queue->front + queue->count) % capacity;
    vector_set(queue->vector, back, data);
    queue->count++;
}

Data queue_get(const Queue *queue)
{
    if (queue->count == 0)
    {
        return (Data)0;
    }
    return vector_get(queue->vector, queue->front);
}

void queue_remove(Queue *queue)
{
    if (queue->count == 0)
    {
        return;
    }
    
    size_t capacity = vector_size(queue->vector);
    queue->front = (queue->front + 1) % capacity;
    queue->count--;
}

bool queue_empty(const Queue *queue)
{
    return queue->count == 0;
}
