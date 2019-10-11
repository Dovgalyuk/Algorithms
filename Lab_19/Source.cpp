#include "queue_test.h"
#include <iostream>
#include "queue.hpp"

int main()
{
	queue_test();
	int a, b;
	std::cin >> a >> b;
	int temp;
	Queue<int> first, second, third;
	while (true)
	{
		std::cin >> temp;
		if (std::cin.eof()) //до этого условие было в while, для файла работает, но с вводом из ostream дублировало последний символ
			break;
		if (temp < a)
			first.insert(temp);
		else if (temp <= b)
			second.insert(temp);
		else
			third.insert(temp);
	}
	while (!first.empty())
	{
		std::cout << first.get() << " ";
		first.remove();
	}
	while (!second.empty())
	{
		std::cout << second.get() << " ";
		second.remove();
	}
	while (!third.empty())
	{
		std::cout << third.get() << " ";
		third.remove();
	}
}