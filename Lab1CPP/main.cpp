#include "array.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>


using namespace std;


void two_small(const Array* arr) {
	size_t n = array_size(arr);
	if (n == 0) {
		cout << "Two smallest elements: none\n";
		return;
	}
	if (n == 1) {
		Data val = array_get(arr, 0);
		cout << "Two smallest elements: " << val << ", " << val << endl;
		return;
	}

	Data min1 = array_get(arr, 0);
	Data min2 = array_get(arr, 1);
	if (min1 > min2) {
		swap(min1, min2);
	}

	for (size_t i = 2; i < n; ++i) {
		Data val = array_get(arr, i);
		if (val <= min1) {
			min2 = min1;
			min1 = val;
		}
		else if (val <= min2) min2 = val;
	}
	cout << "Two smallest elements: " << min1 << ", " << min2 << endl;
}

void unique_elem(const Array* arr) {
	size_t n = array_size(arr);
	bool found = false;

	cout << "Unique elements:";
	for (size_t i = 0; i < n; ++i) {
		Data curr = array_get(arr, i);
		int count = 0;
		for (size_t j = 0; j < n; ++j) {
			if (array_get(arr, j) == curr) count++;
		}

		if (count == 1) {
			cout << " " << curr;
			found = true;
			}
		}

	if (!found) cout << " none";
	cout << endl;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Opened: " << argv[0] << " file>\n";
		return 1;
	}

	ifstream file(argv[1]);

	if (!file.is_open()) {
		cerr << "Cannot open file\n";
		return 1;
	}
	size_t n;
	file >> n;

	if (n == 0) {
		cerr << "Incorrect size\n";
		return 1;
	}
	Array* arr = array_create(n);

	for (size_t i = 0; i < n; ++i) {
		Data value;
		file >> value;
		array_set(arr, i, value);
	}

	file.close();

	two_small(arr);
	unique_elem(arr);

	array_delete(arr);
	return 0;
}
