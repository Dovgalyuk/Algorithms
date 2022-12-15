#include <iostream>
#include <ctime>
#include "array.h"

using namespace std;

void FillArray(Array* arr) {
	srand(time(NULL));
	for (int index = 0; index < array_size(arr); index++) {
		array_set(arr, index, rand() % 201 - 100);
	}
}
void FindArithmMean(const Array* arr){
	double SummArithmMean = 0;
	int CountSize_t = 0;
	for (int index = 0; index < array_size(arr); index++) {
		if (array_get(arr, index) > 0) {
			SummArithmMean += array_get(arr, index);
			CountSize_t++;
		}
	}
	cout << SummArithmMean / CountSize_t;
}
int main()
{
	int SizeArray;
	cout << "Enter array size: ";
	cin >> SizeArray;
	Array* DataMas = array_create(SizeArray);
	FillArray(DataMas);
	FindArithmMean(DataMas);
	array_delete(DataMas);
}
