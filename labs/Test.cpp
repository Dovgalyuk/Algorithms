#include <iostream>
#include "array.h"
using namespace std;

int main()
{
	size_t size;
	cout << "Enter array size: ";
	cin >> size;
	Array* array = array_create(size);
	int negative_numder_count = 0;
	int positive_numder_count = 0;
	
	for (int i = 0; i < array_size(array); i++)
	{
		int random_number = rand()%100-50;
		array_set(array, i, random_number);
		if (random_number >= 0) {
			positive_numder_count++;
		}
		else {
			negative_numder_count++;
		}
	}
	Array* negative_numders = array_create(negative_numder_count);
	Array* positive_numders = array_create(positive_numder_count);
	int last_id_negative_numder_array = 0;
	int last_id_positive_numder_array = 0;
	for (int i = 0; i < array_size(array); i++)
	{
		int number = array_get(array, i);
		if (number >= 0) {
			array_set(positive_numders, last_id_positive_numder_array++, number);
		}
		else {
			array_set(negative_numders, last_id_negative_numder_array++, number);
		}
	}
	
	cout << "Array positive elements: "<<endl;
	for (int i = 0; i < array_size(positive_numders); i++)
	{
		cout << array_get(positive_numders, i)<<endl;
	}
	cout << "Array negative elements: "<<endl;
	for (int i = 0; i < array_size(negative_numders); i++)
	{
		cout << array_get(negative_numders, i)<<endl;
	}
	delete negative_numders;
	delete positive_numders;
	delete array;
}