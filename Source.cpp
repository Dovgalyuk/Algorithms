#include <iostream>
#include "array.h"
#include <ctime>
#include <cmath>
using namespace std;

int main() {
	srand(time(0));
	int n;
	
	cout << "Enter array size" << endl;
	cin >> n;
	cout << endl;
	Array array(n);
	for (int i = 0; i < n; i++) {
		array[i] = rand() % 20 + 1;
	}
	for (int i = 0; i < n; i++){
		cout << array[i] << endl;
		if (array[i] % 2 == 0)
			array[i] = pow(array[i], 2);
		else
			array[i] = array[i] * 2;
		

	}
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << array[i] << endl;
	}


	

}
