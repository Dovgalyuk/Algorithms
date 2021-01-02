#include <iostream>
#include "array.h"

using namespace std;

void do_shift(Array<Data>& arr, unsigned value, string direction)
{
	if (direction == "L")
	{
		for (int i = 0; i < arr.size(); i++)
		{
			if (i <= arr.size() - value - 1) arr.set(i, arr.get(value + i));
			else arr.set(i, 0);
		}
	}
	else if (direction == "R")
	{
		for (int i = arr.size() - 1; i >= 0; i--)
		{
			if (i >= value) arr.set(i, arr.get(i - value));
			else arr.set(i, 0);
		}
	}
	else return;
}

void print_array(Array<Data>& arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr.get(i) << " ";
	}
}

int main()
{
	size_t n;
	cout << "Size of array: ";
	cin >> n;

	Array<Data>* arr = new Array<Data>(n);

	const unsigned rand_value = 11;
	srand(rand_value);

	for (int i = 0; i < n; i++)
	{
		arr->set(i, rand());
	}

	print_array(*arr);
	cout << endl;

	unsigned shift;
	string dir;
	while (cin)
	{
		cout << "Enter required shift and direction (L / R): ";
		cin >> shift >> dir;
		do_shift(*arr, shift, dir);
		
		cout << endl;
		print_array(*arr);
		cout << endl;
	}
}