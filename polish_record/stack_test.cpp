#include <iostream>
#include "stack.hpp"
#include "stack_test.h"

void Stack_test()
{
	Stack<int>* test = new Stack<int>;
	test->push(1);
	test->push(2);
	test->push(3);
	if (test->get() != 3)
		std::cout << "Invalid stack top after push\n";
	std::cout << "Get: " << test->get() << "\n";
	test->pop();
	if (test->get() != 2)
		std::cout << "Invalid stack top after pop\n";
	std::cout << "Get: " << test->get() << "\n";
	test->pop();
	if (test->get() != 1)
		std::cout << "Invalid stack top after pop\n";
	std::cout << "Get: " << test->get() << "\n";
	test->push(4);
	test->push(5);
	if (test->get() != 5)
		std::cout << "Invalid stack top after push\n";
	while (!test->empty())
	{
		std::cout << "Get: " << test->get() << "\n";
		test->pop();
	}
	delete test;
}