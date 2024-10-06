#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "array.h"

Array* array_create_read(std::ifstream& input);
void total_resistance(Array* arr);
void most_number(Array* arr);

int main(int argc, char **argv) {
	setlocale(LC_ALL, "RU");

	if (argc < 2) {
		std::cerr << "Ошибка, укажите путь к файлу" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open()) {
		std::cerr << "Ошибка открытия файла: " << argv[1] << "\n";
		return 1;
	}

	Array* arr = array_create_read(input);
	total_resistance(arr);
	array_delete(arr);

	arr = array_create_read(input);
	most_number(arr);
	array_delete(arr);

	input.close();

	return 0;
}

Array* array_create_read(std::ifstream& input) {
	size_t size;
	input >> size;

	Array* arr = array_create(size);

	for (size_t i = 0; i < size; ++i) {
		int x;
		input >> x;
		array_set(arr, i, x);
	}
	return arr;
}

void total_resistance(Array* arr) {
	double resistance = 0.0;
	for (size_t i = 0; i < array_size(arr); ++i) {
		resistance += (1.0 / array_get(arr, i));
	}
	
	std::cout << "Общее сопротивление: " << resistance << std::endl;
}

void most_number(Array* arr) {
	int maxCount = 0;
	int result = 0;
	for (size_t i = 0; i < array_size(arr); ++i) {
		int count = 0;
		for (size_t j = 0; j < array_size(arr); ++j) {
			if (array_get(arr, i) == array_get(arr, j))
				count++;
		}
		if (count > maxCount) {
			maxCount = count;
			result = array_get(arr, i);
		}
	}
	std::cout << "Чаще всего встречает: " << result << std::endl;
}