#include "queue.h"
#include "vector.h" 

struct Queue
{
    Vector* data;  // ������������� ���������� "vector" ��� �������� ������
};

Queue* queue_create()
{
    Queue* queue = new Queue;
    queue->data = vector_create();
    return queue;
}

void queue_delete(Queue* queue)
{
    vector_delete(queue->data);
    delete queue;
}

void queue_insert(Queue* queue, Data data)
{
    // ������� �������� � ����� �������
    vector_resize(queue->data, vector_size(queue->data) + 1);
    vector_set(queue->data, vector_size(queue->data) - 1, data);
}

Data queue_get(const Queue* queue)
{
    // ��������� �������� �� ������ �������
    if (!queue_empty(queue))
    {
        return vector_get(queue->data, 0);
    }
    else
    {
        // ���������� �����-�� ��������� Data � ������ ������ �������
        return (Data)0;
    }
}

void queue_remove(Queue* queue)
{
    // �������� �������� �� ������ �������
    if (!queue_empty(queue))
    {
        // �������� ��� �������� �����
        for (size_t i = 1; i < vector_size(queue->data); ++i)
        {
            vector_set(queue->data, i - 1, vector_get(queue->data, i));
        }
        // ��������� ������ �� 1
        vector_resize(queue->data, vector_size(queue->data) - 1);
    }
}

bool queue_empty(const Queue* queue)
{
    return vector_size(queue->data) == 0;
}