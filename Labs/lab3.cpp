#include<iostream>
#include<fstream>
#include <cmath> 
#include "queue.h"

// 0000..1111 only 1-15 numbers
const int MAX_DIGITS = 4;

int get_bit(
	const int num, 
	const int pos,
	const int count
) {
	int result = 0;
	for (int i = 0; i < count; ++i) {
		result |= (num & (1 << (pos + i))) >> pos;
	}
	return result;
}

void radix_sort(Queue* queue) {
	
	const int RADIX = 4;

	int offset = sqrt(RADIX);

	//Creating buckets
	Queue* buckets[RADIX];
	for (int i = 0; i < RADIX; ++i) buckets[i] = queue_create();

	for (int i = 0; i < MAX_DIGITS; i += offset) {
		
		while (!queue_empty(queue)) {
			int num = queue_get(queue);
			queue_insert(buckets[get_bit(num,i,offset)],num);
			queue_remove(queue);
		}

		for (int i = 0; i < RADIX; ++i) {
			while (!queue_empty(buckets[i])) {
				queue_insert(queue, queue_get(buckets[i]));
				queue_remove(buckets[i]);
			}
		}
	}

	//Clear backets
	for (int i = 0; i < RADIX; ++i) queue_delete(buckets[i]);

}

void queue_print(Queue* queue) {

	while (!queue_empty(queue)) {
		std::cout << queue_get(queue) << " ";
		queue_remove(queue);
	}
}

Queue* read_numbers_from_file(const std::string filename) {
	
	std::ifstream file(filename);

	if (!file.is_open()) exit(1);

	Queue* queue = queue_create();
	
	int num;
	while (file >> num) queue_insert(queue,num);
	
	file.close();

	return queue;
}

int main(int argc,char* argv[]) {
	
	//Get the file path from arguments
	Queue* queue = read_numbers_from_file(argv[1]);

	radix_sort(queue); 
	queue_print(queue);

	queue_delete(queue);
}