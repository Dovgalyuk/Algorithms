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

	if ((tmp = deque_size(deque)) != 200) {
		std::cout << "Invalid deque size after push back " << tmp << "\n";
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		if ((tmp = deque_get(deque, i)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " after psuh back\n";
		}
	}

	for (int i = 0; i < 100; i++) {
		if ((tmp = deque_last(deque)) != 199 - i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " in process of pop back\n";
		}
		deque_pop_back(deque);
	}

	if ((tmp = deque_size(deque)) != 100) {
		std::cout << "Invalid deque size after pop back " << tmp << "\n";
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		if ((tmp = deque_get(deque, i)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " after pop back\n";
		}
	}

	size_t size = deque_size(deque);

	for (size_t i = 0; i < size;i++) {
		deque_pop_back(deque);
	}

	if (deque_size(deque) != 0) {
		std::cout << "Not zero size after clearing with pop back\n";
	}

	for (int i = 0; i < 10; i++) {
		deque_set(deque, i, i + 190);
	}

	for (int i = 0; i < 190; i++) {
		deque_push_front(deque, 189 - i);
	}

	if ((tmp = deque_size(deque)) != 200) {
		std::cout << "Wrong size afeter push front " << tmp << "\n";
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		if ((tmp = deque_get(deque, i)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " after psuh front\n";
		}
	}

	for (int i = 200; i < 300; i++) {
		deque_push_back(deque, i);
	}

	if ((tmp = deque_size(deque)) != 300) {
		std::cout << "Wrong size afeter mixed push " << tmp << "\n";
	}

	for (size_t i = 0; i < deque_size(deque); i++) {
		if ((tmp = deque_get(deque, i)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " after mixed psuh\n";
		}
	}

	size = deque_size(deque);

	for (size_t i = 0; i < size; i++) {
		if ((tmp = deque_first(deque)) != i)
		{
			std::cout << "Invalid deque element " << i << " " << tmp << " in prcess of pop front\n";
		}
		deque_pop_front(deque);
	}

	if (deque_size(deque) != 0) {
		std::cout << "Not zero size after clearing with pop front\n";
	}

	deque_delete(deque);
}
