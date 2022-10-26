#include <iostream>
#include "list.h"
#include "queue.h"

using namespace std;

void show_queue(Queue *queue){
	while (queue_empty(queue)) {
		cout << queue_get(queue) << " ";
		queue_remove(queue);
	}
}


int main()
{
	Queue *queue = queue_create();

	queue_insert(queue, 1);
	queue_insert(queue, 2);
	queue_insert(queue, 3);
	queue_insert(queue, 4);
	queue_insert(queue, 5);

	show_queue(queue);
}
