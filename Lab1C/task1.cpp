#include <iostream>
#include <fstream>
#include "array.h"

using namespace std;


int main(int args, char* argv[]) {
	if (args < 2){
		return 1;
	}

	ifstream input(argv[1]);

	int n;
	input >> n;

	Array* arr = array_create(n);
	for (size_t  i = 0; i < n; i++) {
		int x;
		input >> x;
		array_set(arr, i, x);
	}

	long long sum = 0;

	for (size_t  i = 0; i < n; i++) {
		sum += array_get(arr, i);
	}

	int count = 0;

	for (size_t i = 0; i < n; i++) {
		if (array_get(arr, i) > sum) {
			count++;
		}
	}

	cout << count;

	for (size_t i = 0; i < n; i++) {
		if (array_get(arr, i) > sum) {
			cout << " " << i;
		}
	}

	cout << "\n";
	array_delete(arr);

	return 0;
}