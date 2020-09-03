#include <iostream>

using namespace std;

int main()
{
	int arr_size, average;
	int sum = 0;
	cout << "Enter the size of array: ";
	cin >> arr_size;
	cout << endl;
	int *arr = new int[arr_size];

	for (int i = 0; i < arr_size; i++)
	{
		arr[i] = rand() % 201 - 100;
		sum += arr[i];
		cout << arr[i] << endl;
	}

	average = sum / arr_size;
	cout << "The average is: " << average << endl;
	cout << "Elements meeting the condition:" << endl;

	for (int i = 0; i < arr_size; i++)
	{
		if (arr[i] < average)
		{
			cout << "arr[" << i << "] = " << arr[i];
			cout << endl;
		}
	}

	delete[] arr;
	return 0;
}