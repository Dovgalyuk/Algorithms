#include <iostream>
#include "array.h"
#include <ctime> 


using namespace std;

int count(Array *arr, Data value) { //Вычисление колличества одинаковых оценок
	int znach = 0;
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {
		if (array_get(arr, i) == value) {
			znach += 1;
		}
	}
	return znach;
}

void conclusion(Array *arr) { //Вывод на экран массива
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {
		cout << array_get(arr, i) << " ";
	}
}


void task1(Array *arr)
{
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {
		array_set(arr, i, 2 + rand() % 4); //Заполнение массива числами от 2 до 5
	}
	cout << "Foreign language grades:" << endl;
	conclusion(arr);
	cout << endl;
	for (Data i = 2; i < 6; i++) {
		cout << "Quantity " << i << ": " << count(arr, i) << " " << endl;
	}


}

void task2(Array *arr)
{
	size_t size = array_size(arr);
	for (size_t i = 0; i < size; i++) {//заполнение массива числами от 0 до 99
		array_set(arr, i, rand() % 100);
	}
	cout << "Values in array:" << endl;
	conclusion(arr);
	cout << endl;
	cout << "Elements that appear exactly twice:" << endl;
	for (size_t i = 0; i < size; i++) { //Нахождение элементов которые встречаются ровно два раза
		Data a = array_get(arr, i);
		int quantity = 1;
		for (size_t j = 0; j < size; j++) {
			if ((a == array_get(arr, j)) && (i != j)) {
				quantity += 1;
			}
		}
		if (quantity == 2) {
			cout << a << " ";
			array_set(arr, i, -a);
		}
	}
}

void examination(size_t &size) { //Проверка на правльный ввод
	while (true) {
		cin >> size;
		if (!cin.fail()) {
			break;
		}
		else {
			cout << "Enter again:" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
	}
}



int main()
{
	srand(time(NULL));
	Array *arr = NULL;
	size_t size;
	cout << "Enter array length:";
	examination(size);
	arr = array_create(size);
	/* Create array here */
	task1(arr);
	array_delete(arr);
	/* Create another array here */
	cout << "Enter array length:";
	examination(size);
	arr = array_create(size);
	task2(arr);
	array_delete(arr);
}
