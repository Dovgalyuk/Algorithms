#ifndef QUEUE_H
#define QUEUE_H

// В данном случае в очереди хранятся данные типа int,
// поэтому функции работы с очередью принимают и возвращают 
// данные этого типа
struct Queue;

// создание пустой очереди
Queue *queue_create();

// удаление очереди
void queue_delete(Queue *queue);

// включение элемента в очередь
void queue_insert(Queue *queue, int data);

// получение первого элемента очереди
int queue_get(Queue *queue);

// удаление первого элемента из очереди
void queue_remove(Queue *queue);

// проверка очереди на наличие элементов
bool queue_empty(Queue *queue);

#endif
