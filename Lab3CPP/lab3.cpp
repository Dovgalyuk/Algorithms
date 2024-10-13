#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"

int main() {
	std::ifstream in("input.txt");
	Vector* vector = vector_create();
	if (in) {
		char temp = '1';
		while (in.get(temp)) {
			if(temp != '\n')
				vector_push(vector, temp);
		}

		for (size_t i = 0; i < vector_size(vector); i++) {
			if (i % 6 == 0 && i != 0)
				std::cout << "\n";
			std::cout << (char)vector_get(vector, i);
		}
	}
	in.close();
	return 0;
}