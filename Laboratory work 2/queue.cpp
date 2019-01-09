
#include "pch.h"
#include <stdlib.h>
#include "queue.h"
#include "vector.h"
#include <iostream>

using namespace std;

struct Queue
{
	Vector *vector;
	Data head;
	Data tail;
};

Queue *queue_create()
{
	Queue *NewQueue;

	try
	{
		NewQueue = new Queue;
		NewQueue->vector = vector_create();
	}
	catch (bad_alloc xa)
	{
		cout << "Queue didn't created" << endl;
		return NULL;
	}
	NewQueue->head = 0;
	NewQueue->tail = 0;

	return NewQueue;
}

void queue_delete(Queue *queue)
{
	vector_delete(queue->vector);
	delete queue;
}

void queue_insert(Queue *queue, Data data)
{
	if (queue->head == 0 )
	{
		if (queue->tail == vector_size(queue->vector) - 1)
		{

			vector_resize(queue->vector, vector_size(queue->vector) + 1);
			vector_set(queue->vector, queue->tail, data);
			queue->tail++;

		}
		else
		{
			vector_set(queue->vector, queue->tail, data);
			queue->tail++;
		}
	}
	else if (queue->head != 0 )
	{
		if (queue->tail == vector_size(queue->vector) - 1)
		{
			vector_set(queue->vector, queue->tail, data);
			queue->tail = 0;
		}
		else
		{
			if (queue->head != queue->tail + 1)
			{
				vector_set(queue->vector, queue->tail, data);
				queue->tail++;
			}
			else
			{
				Vector *NewVector = vector_create();
				vector_resize(NewVector, vector_size(queue->vector)+1);
				int count = 0;
				for (size_t i = queue->head; i < vector_size(queue->vector); i++)
				{
				
					vector_set(NewVector, count, vector_get(queue->vector, i));
					count++;
				}

				queue->head = 0;
				for (size_t i = 0; i < queue->tail; i++)
				{
					vector_set(NewVector, count, vector_get(queue->vector, i));
					count++;
				}
				vector_set(NewVector, count, data);
				vector_delete(queue->vector);
				queue->vector = NewVector;
				queue->tail = vector_size(queue->vector) - 1;
				
			}
		}
	}
	
	
}

Data queue_get(Queue *queue)
{
	return vector_get(queue->vector, queue->head);
}

void queue_remove(Queue *queue)
{
	if (queue->head == vector_size(queue->vector)-1)
	{
		queue->head = 0;
	}
	else 
	{
		queue->head++;
	}
	
}

bool queue_empty(Queue *queue)
{
	if (queue->tail == queue->head)return true;
	else
	{
		return false;
	}
}
