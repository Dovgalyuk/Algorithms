#include "../LibraryCPPClass/array.h"
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

int main(){
	std::ifstream file("input.txt");
	int size1;
	file >> size1;

	for (int i = 0; i < size1; i++) {
		int temp;
		file >> temp;
	}

	Array arr1(size1);
	int num = 0;
	for (size_t i = 0; i < arr1.size(); i++) {
		while (!is_palindrome(num)) num++;
		arr1.set(i, num);
		num++;
	}

	for (int i = 0; i < size1; i++) {
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


