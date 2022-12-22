#include <iostream>
#include <ctime>
using namespace std;

int main()
{

	int arr_size, *arr, counter = 0, num1 = 0, num2;

	cout << "Enter array size: ";
	cin >> arr_size;
	arr = new int[arr_size];

	srand(time(NULL));
	cout << "Array: ";
	for (int i = 0; i < arr_size; i++) {
		arr[i] = 1 + rand() % 10;
		cout << arr[i] << " ";
	}

	cout << endl << "Element repeated 2 times: ";

	for (int i = 0; i < arr_size; i++, counter = 0)
	{
		for (int j = 0; j < arr_size; j++)
			if (arr[i] == arr[j])
				counter++;
		if (counter == 2)
		{
			num2 = num1;
			num1 ^= arr[i];
			if (num2 > num1)
				cout<<arr[i]<<" ";
		}

	}
	delete[] arr;
	return 0;
}