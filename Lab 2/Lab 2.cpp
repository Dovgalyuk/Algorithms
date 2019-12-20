#include <iostream>
#include <fstream>
#include <queue.h>
#include "stack.h"
using namespace std;

void in(Queue *q, ifstream &file) {
	int g, i, n;
	file >> g;
	for (i = 0; i < g; i++) {
		file >> n;
		queue_insert(q, n);
	}
};

void out(Queue* q, int n) {
	cout << n << " " << queue_get(q) << endl;
	queue_remove(q);
};

int main() {
	Queue* q1 = queue_create();
	Queue* q2 = queue_create();
	Queue* q3 = queue_create();
	ifstream file("file.txt");

	if (!file)
	{
		cout << "Error!" << endl;
		return 0;
	}
	in(q1, file);
	in(q2, file);
	in(q3, file);

	while (!queue_empty(q1) || !queue_empty(q2) || !queue_empty(q3)) {
		if (queue_get(q1) < queue_get(q2) && queue_get(q1) < queue_get(q3) && !queue_empty(q1))
			out(q1, 1);
		else if (queue_get(q2) < queue_get(q3) && !queue_empty(q2))
			out(q2, 2);
		else
			out(q3, 3);
	}
}


