#include "list.h"
#include "queue.h"

// Структура "ListItem" была продублирована из-за тупика в queue_remove ("message": "использование неопределенного типа \"ListItem\""),
// Необходимо при удалении переместить tail на предыдущую позицию
// Но список односвязный и поэтому я знаю значение только следующего элемента
// Я рассмотрел вариант, при котором список перевернётся и добавится хвост (tail), а каждое значение будет знать своё предыдущее.
// В таком случае падает скорость обращения к следующему элементу, а также удаления следущего элемента O(1) --> O(N),
// но появляется возможность обращения к предущему со скоростью O(1) и отпадает необходимость костыльного дублирования
// Такой вариант вполне реализуем
// Павел Михайлович, хотел у вас узнать, имеет ли подобное смысл или оставить с продублированной структурой?
struct ListItem
{
    Data data;
    ListItem* pNext;
};

struct Queue
{
    List* data;
    ListItem* head;
    ListItem* tail;
};

Queue *queue_create()
{
    Queue* temp = new Queue;
    temp->data = list_create();
    temp->head = temp->tail = nullptr;
    return temp;
}

void queue_delete(Queue *queue)
{
    list_delete(queue->data);
    delete queue;
}

void queue_insert(Queue *queue, Data data)
{
    if (queue_empty(queue)) {
        list_insert(queue->data, data);
        queue->head = queue->tail = list_first(queue->data);
    } else {
        list_insert(queue->data, data);
        queue->head = list_first(queue->data);
    }
}

Data queue_get(const Queue *queue)
{
    return list_item_data(queue->tail);
}

void queue_remove(Queue *queue)
{
    
    if (queue->head->pNext) {
        ListItem* temp = queue->head;
        while (temp->pNext != queue->tail)
        {
            temp = temp->pNext;
        }
        list_erase_next(queue->data, temp);
        queue->tail = temp;
    } else {
        list_erase_first(queue->data);
        queue->head = queue->tail = nullptr;
    }

}

bool queue_empty(const Queue *queue)
{
    return (queue->head == nullptr);
}
