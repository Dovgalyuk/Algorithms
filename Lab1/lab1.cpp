#include <iostream>
#include "array.h"

using namespace std;

int main()
{
	//test
	Array* arr = array_create(10);

	if (array_size(arr) != 10)
	{
		std::cout << "Invalid array size\n";
		return 1;
	}

	for (int i = 0; i < 10; ++i)
		array_set(arr, i, i * 2);

	for (int i = 0; i < 10; ++i)
	{
		if (array_get(arr, i) != i * 2)
		{
			std::cout << "Invalid array element " << i << "\n";
			return 1;
		}
	}

	array_delete(arr);

	//Task
	int a, mx = 0, sum, p;
	Array* A = NULL;
	cin >> a;
	A = array_create(a);
	for (int i = 0; i < a; i++)
	{
		array_set(A, i, rand()%51);
	}
	for (int i = 0; i < a - 5; i++)
	{
		sum = 0;
		for (int j = i; j < i + 5; j++)
		{
			sum += array_get(A, j);
		}
		if (mx < sum)
		{
			mx = sum;
			p = i;
		}
	}
	for (int i = 0; i < a; i++)
	{
		cout << array_get(A, i) << " ";
	}
	cout << endl;
	for (int i = p; i < p + 5; i++)
	{
		cout<<array_get(A, i)<<" ";
	}
	array_delete(A);
}
