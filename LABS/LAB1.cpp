#include <iostream>
#include "array.h"
#include <ctime>
#include <cmath> 
using namespace std;

void array_function(Array* arr) {
	int chet = 0;
	int nechet = 0;
	cout << "first massive" << endl;
	for (int i = 0; i < array_size(arr); i++) {
		array_set(arr, i, rand() % 20 + 1);
		cout  << array_get(arr, i) << endl;
	}
	cout << endl;
	cout << "itogoviy massive" << endl;
	
	for (int i = 0; i < array_size(arr); i++) {
		if (array_get(arr, i) % 2 == 0) {

			chet = array_get(arr, i);
			chet = pow(chet,2);
			cout << chet << endl;
		}
		else {
			nechet = array_get(arr, i);
			nechet *= 2;
			cout << nechet << endl;
		}
		
	}

}

int main() {

	srand(time(0));
	int n;

	cout << "Enter array size" << endl;
	cin >> n;
	cout << endl;
	
	Array* arr = array_create(n);

	array_function(arr);
	
	array_delete(arr);

}