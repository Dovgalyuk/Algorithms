#include <iostream>
#include <string>



int main()
{
	int M;
	std::cin >> M;
	array<int, M> A;
	for (int i = 0; i < M; i++)
	{
		std::cin >> A[i];
	}
	int ch = 0;
	for (int i = 1; i < M; i++)
	{
		if ((A[i - 1] >= 0) != (A[i] >= 0))
		{
			ch++;
		}
	}
	std::cout << ch;
}
