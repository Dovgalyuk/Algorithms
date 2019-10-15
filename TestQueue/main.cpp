#include <iostream>
#include "queue.hpp"

int main()
{
	Queue<int>* test = new Queue<int>;

	test->insert(1);
	test->insert(2);
	test->insert(3);

	if (test->get() != 1)
		std::cout << "Invalid first element of the queue\n";

	std::cout << "Get: " << test->get() << "\n";
	test->remove();

	if (test->get() != 2)
		std::cout << "Invalid second element of the queue\n";

	std::cout << "Get: " << test->get() << "\n";
	test->remove();

	if (test->get() != 3)
		std::cout << "Invalid third element of the queue\n";

	std::cout << "Get: " << test->get() << "\n";
	test->insert(4);
	while (!test->empty())
	{
		std::cout << "Get: " << test->get() << "\n";
		test->remove();
	}

	delete test;
}