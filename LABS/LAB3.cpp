#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"
using namespace std;

void in(Queue* queue, ifstream& file) {
	int quantity, moment;
	file >> quantity;
	for (int i = 0; i < quantity; i++) {
		file >> moment;
		queue_insert(queue, moment);
	}
}

void out(Queue* queue, int Queue_number) {
	cout << Queue_number << " " << queue_get(queue) << endl;
	queue_remove(queue);
}

int main() {
	Queue* queue1 = queue_create();
	Queue* queue2 = queue_create();
	Queue* queue3 = queue_create();
	ifstream file("file.txt");

	if (!file)
	{
		cout << "error!" << endl;
		return 0;
	}
	in(queue1, file);
	in(queue2, file);
	in(queue3, file);
	while (!queue_empty(queue1) || !queue_empty(queue2) || !queue_empty(queue3)) {
		if (queue_get(queue1) < queue_get(queue2) && queue_get(queue1) < queue_get(queue3) && !queue_empty(queue1))
			out(queue1, 1);
		else if (queue_get(queue2) < queue_get(queue3) && !queue_empty(queue2))
			out(queue2, 2);
		else
			out(queue3, 3);
	}
}