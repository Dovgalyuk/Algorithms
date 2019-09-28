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
	for (int i = 0; i < 10; i++) {
		if (deque_get(deque, i) != i)
		{
			std::cout << "Invalid deque element " << i << "\n";
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
}
