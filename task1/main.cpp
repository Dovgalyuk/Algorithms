#include <iostream>
#include <ctime>
#include "array.h"

int main()
{
	int N;
	std::cout << "Set Array's size:";
	std::cin >> N;

	Array* arr = array_create(N);

	srand(time(NULL));

	for (int i = 0; i < N; ++i)
	{
		array_set(arr, i, rand() % 200 - 100);
		std::cout << array_get(arr, i) << " ";
	}
	
	int temp;

	for (int i = 0; i < N / 2; i++)
	{
		temp = array_get(arr, N - i - 1);
		array_set(arr, N - i - 1, array_get(arr, i));
		array_set(arr, i, temp);

	}

	std::cout << "Result after reverse sorting:" << std::endl;

	for (int i = 0; i < N; ++i)
	{
		std::cout << array_get(arr, i) << " ";
	}

	system("pause");
	return 0;
}