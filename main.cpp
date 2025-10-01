#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Array {
	int* elem;
	int size;
};

Array construct_array(int n) {
	Array arr;
	arr.size = n;
	arr.elem = new int[n];
	return arr;
}

void destruct_array(Array& arr) {
	delete[] arr.elem;
	arr.elem = nullptr;
	arr.size = 0;
}

bool read_array(const string & input, Array& arr) {
	ifstream inp(input);
	
	if (!inp.is_open()) return false;
	int n;

	if (!(inp >> n)) return false;
	
	if (n <= 0) return false;

	Array temp = construct_array(n);

	for (int i = 0; i < n; i++) {
		if (!(inp >> temp.elem[i])) {
			destruct_array(temp);
			inp.close();
			return false;
		}
	}

	arr = temp;
	inp.close();
	return true;

}


void two_small(const Array& arr) {
	int n = arr.size;
	int min1;
	int min2;
	if (arr.size <= 0) {
		cout << "zero array \n";
		return;
	}
	if (n == 1) {
		min1 = arr.elem[0];
		min2 = arr.elem[0];
		cout << "Two smallest: " << min1 << ", " << min2 << endl;
	}
	if (n >= 2){
		if (arr.elem[0] < arr.elem[1]) min1 = arr.elem[0], min2 = arr.elem[1];
		else min1 = arr.elem[1], min2 = arr.elem[0];
		for (int i = 2; i < n; i++) {
			if (min1 > arr.elem[i]) {
				min2 = min1;
				min1 = arr.elem[i];
			}
			else if (min2 > arr.elem[i]) min2 = arr.elem[i];
		}
		cout << "Two smallest: " << min1 << ", " << min2 << endl;
	}

}

void unique_elem(const Array& arr) {
	int n = arr.size;
	cout << "Unique elements: ";
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (arr.elem[j] == arr.elem[i]) {
				count++;
			}
		}
		if (count == 1) {
			cout << arr.elem[i] << " ";
		}
	}
	cout << endl;
}

int main()
{
	Array arr;
	if (!read_array("input.txt", arr)) {
		cout << "Invalid" << endl;
		return 1;
	}
	two_small(arr);
	unique_elem(arr);
	destruct_array(arr);
	return 0;
}
