#include <iostream>
#include <fstream>
#include <cmath> 
#include "queue.h"

using namespace std;

void radixSort(Queue* queue) {
	const int limitBit = 4;

	const int bitSort = 3;

	const int bitsKit = 1 << bitSort;

	Queue* collection[bitsKit];

	for (int i = 0; i < bitsKit; i++)
	{
		collection[i] = queue_create();
	}
	
	for (int i = 0; i < limitBit; i++)
	{
		while (!queue_empty(queue)) {
			int num = queue_get(queue);
			queue_insert(collection[(num >> i) & 1], num);
			queue_remove(queue);
		}

		for (int i = 0; i < bitsKit; i++)
		{
			while (!queue_empty(collection[i])) {
				queue_insert(queue, queue_get(collection[i]));
				queue_remove(collection[i]);
			}
		}
	}

	for (int i = 0; i < bitsKit; i++)
	{
		queue_delete(collection[i]);
	}
}

int main() {

	Queue* queue = queue_create();

	ifstream file("1.txt");

	if (!file.is_open()) {
		cout << "Error! File 1.txt isn't exist";
		exit;
	}
	else {
		while (!file.eof()) {
			int num;
			file >> num;
			queue_insert(queue, num);
		}
		file.close();
	}

	radixSort(queue);

	while (!queue_empty(queue)) {
		std::cout << queue_get(queue) << " ";
		queue_remove(queue);
	}

	queue_delete(queue);
}
