#include <iostream>
#include "deque.h"

int main()
{
	Deque* deque = deque_create();

	Data tmp;

	if ((tmp = deque_size(deque)) != 0) {
		std::cout << "Invalid empty deque size " << tmp << "\n";
	}
	for (int i = 0; i < 10; i++) {
		deque_set(deque, i, i);
	}
	for (size_t i = 0; i < deque_size(deque); i++) {
		if (deque_get(deque, i) != i)
		{
			std::cout << "Invalid deque element " << i << " after set\n";
		}
	}
	if ((tmp = deque_first(deque)) != 0) {
		std::cout << "Invalid first deque element " << tmp << "\n";
	}
	if ((tmp = deque_last(deque)) != 9) {
		std::cout << "Invalid last deque element " << tmp << "\n";
	}
	if ((tmp = deque_size(deque)) != 10) {
		std::cout << "Invalid deque size " << tmp << "\n";
	}

	for (int i = 0; i < 190; i++) {
		deque_push_back(deque, i + 10);
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		if ((tmp = deque_get(deque, i)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " after psuh back\n";
		}
	}

	for (int i = 0; i < 100; i++) {
		deque_pop_back(deque);
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		if ((tmp = deque_get(deque, i)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " after pop back\n";
		}
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		deque_pop_back(deque);
	}

	if (deque_size(deque) != 0) {
		std::cout << "Not zero size after clearing with pop back\n";
	}
}
