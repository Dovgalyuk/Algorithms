#include <iostream>
#include "array.h"

using namespace std;

int main()
{
	int a, mx = 0, sum, p;
	Array* A = NULL;
	cin >> a;
	A = array_create(a);
	for (int i = 0; i < a; i++)
	{
		array_set(A, i, rand()%51);
	}
	sum = 0;
	for (int j = 0; j < 5; j++)
	{
		sum += array_get(A, j);
	}
	mx = sum;
	p = 0;
	for (int i = 1; i < a - 5; i++)
	{
		sum += array_get(A, i + 4) - array_get(A, i - 1);
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
