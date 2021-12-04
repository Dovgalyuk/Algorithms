#include <iostream>
#include <cstdlib>
#include <ctime>
#include "array.cpp"

using namespace std;

int GiveMeSize() {
	int size;
	bool check;
	do {
		cout << "Give me size of the massive: ";
		cin >> size;
		if (cin.fail())
		{
			check = false;
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "\nOh-oh, looks like you made a mistake. Here is your next chanse\n";
		}
		else {
			check = true;
		}
	} while (check == false);
	cout << "\n";
	return size;
}

void FillingArray(Array* array) {
	srand(time(nullptr));
	cout << "We got this:\n";
	for (int i = 0; i < array_size(array); i++) {
		array_set(array, i, rand() % 41 - 20);
		cout << i + 1 << " element: " << array_get(array, i) << "\n";
	}
	cout << "\n";
}

int main()
{
	int size = GiveMeSize();
	Array* array = array_create(size);
	FillingArray(array);
	int summ = 0;
	for (int i = 0; i < size; i++)
	{
		summ = summ + array_get(array, i);
	}
	for (int i = 0; i < size; i++)
	{
		if (array_get(array, i) > summ)
		{
			cout << i + 1 << "\n";
		}
	}
	array_delete(array);
	return 0;
}
