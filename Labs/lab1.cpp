#include <iostream>
#include "array.h"

using namespace std;

int get_size() {
	int size;
	cout << "input size: ";
	cin >> size;
	return size;
}
void show_array(string message, Array* arr, int size) {
	cout << message;
	for (size_t i = 0; i < size; i++) { cout << array_get(arr, i) << " "; }
	cout << "\n";
}
void input(Array* arr, int size) {
	for (size_t i = 0; i < size; i++) { array_set(arr, i, rand() % 100); }
}
void algorithm(Array* arr, int size) {
	for (size_t i = 0; i < size / 2; i++) {
		int value = array_get(arr, size - i - 1);
		array_set(arr, size - i - 1, array_get(arr, i));
		array_set(arr, i, value);
	}
}
void run() {
	int size = get_size();
	Array* first_arr = array_create(size);
	input(first_arr, size);
	show_array("first array: ", first_arr, size);
	algorithm(first_arr, size);
	show_array("second array: ", first_arr, size);
	cout << "\n\n";
	array_delete(first_arr);
}

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	
	run();

	return 0;
}