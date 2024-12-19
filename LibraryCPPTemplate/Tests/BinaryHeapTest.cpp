// Test

#include <string>
#include <iostream>
#include "BinaryHeap.h"

bool less(const std::string& a, const std::string& b) {
	return a < b;
}

int main() {
	BinaryHeap<std::string, less> heap;
	if (!heap.is_empty()) {
		std::cout << "invalid is_empty()";
		return 1;
	}

	heap.push("Hello");
	heap.push("Hell");
	heap.push("Hel");

	if (heap.is_empty()) {
		std::cout << "invalid insertion";
		return 2;
	}

	if (heap.top() != "Hel") {
		std::cout << "Invalid top()\nTop: " << heap.top();
		return 3;
	}

	heap.pop();
	heap.pop();

	std::string temp = heap.pop();
	if (temp != "Hello") {
		std::cout << "Invalid pop()\nPop: " << temp;
		return 4;
	}

	std::cout << "All tests were passed!";

	return 0;
}