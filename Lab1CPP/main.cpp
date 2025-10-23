#include "array.h"
#include <iostream>
#include <fstream>

using namespace std;

bool is_palindrome(int n) {
	if (n < 10) return true;
	int start = n;
	int reversed = 0;
	while (n > 0) {
		reversed = reversed * 10 + n % 10;
		n /= 10;
	}
	return start == reversed;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		cout << "Error: File not specified" << endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	if (!file.is_open()) {
		cout << "Error: Cannot open file " << argv[1] << endl;
		return 1;
	}
	
	int size1;
	file >> size1;

	Array arr1(size1);
	size_t num = 0;
	for (int i = 0; i < size1; i++) {
		int temp;
		file >> temp;
		if (is_palindrome(temp)) {
			arr1.set(num, temp);
			num++;
		}
	}

	for (size_t i = 0; i < num; i++) {
		for (size_t j = 0; j < num - i - 1; j++) {
			if (arr1.get(j) > arr1.get(j + 1)) {
				int a = arr1.get(j);
				int b = arr1.get(j + 1);
				swap(a, b);
				arr1.set(j, a);
				arr1.set(j + 1, b);
			}
		}
	}

	for (size_t i = 0; i < num; i++) {
		cout << arr1.get(i) << " ";
	}
	cout << endl;

	int size2;
	file >> size2;

	Array arr2(size2);
	for (size_t i = 0; i < arr2.size(); i++) {
		int val;
		file >> val;
		arr2.set(i, val);
	}


	for (size_t i = 0; i < arr2.size(); i++) {
		int count = 0;
		for (size_t j = 0; j < arr2.size(); j++) {
			if (arr2.get(i) == arr2.get(j)) count++;
		}
		if (count == 1) {
			cout << arr2.get(i) << " ";
		}
	}
	
	file.close();
	
	return 0;
}


