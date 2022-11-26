#include <iostream>
#include "array.h"



int main()
{
	int M;
	std::cin >> M;
	Array A(M);
	for (int i = 0; i < M; i++)
	{
		int p;
		std::cin >> p;
		array_set(A, i, p);
	}
	int ch = 0;

	for (int i = 1; i < M; i++)
	{
		if ((array_get(A, i - 1) >= 0) != (array_get(A, i) >= 0))
		{
			ch++;
		}
	}
	std::cout << ch;
}