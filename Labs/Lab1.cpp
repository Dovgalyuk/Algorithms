#include <iostream>
#include <ctime>

int Sum(int* a, int size) {
	int res = 0;
	for (int i = 0; i < size; i++)
		if (a[i] <= 20)
			res += a[i];
	return res;
}

void FillingArray(int* a, int size) {
	srand(time(NULL));
	for (int i = 0; i < size; i++)
		a[i] = rand() % 201 - 100;
}

int main() {

	int n;
	std::cout << "Size: ";
	std::cin >> n;
	const int size = n;

	int* array = new int[size];
	FillingArray(array, size);

	std::cout << "Sum: " << Sum(array, size) << '\n';
	delete[] array;
}