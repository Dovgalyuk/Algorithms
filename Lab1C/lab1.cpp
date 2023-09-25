#include <iostream>
#include "array.h"

using namespace std;

void create(Array*& arr) { //функция создания и заполнения массива случайными числами
	size_t size; //размер массива
	cout << "Enter array's size: ";
	while (true) { //обработка неверного ввода
		cin >> size;
		if (!cin.fail()) { //если нет ошибки в вводе, то выходим из цикла, иначе спрашиваем снова
			break;
		}
		else {
			cout << "Incorrect input" << endl;
			cin.clear(); //возвращаем cin в обычный режим работы 
			cin.ignore(32767, '\n'); //и удаляем значения предыдущего ввода из входного буфера
		}
	}
	arr = array_create(size); //выделение памяти для массива
	for (size_t i = 0; i < size; i++) { //перебор массива 
		array_set(arr, i, rand() % 100); //присваиваем случайное число от 0 до 100
	}
}

void print(const Array* arr) { //функция печати массива
	size_t size = array_size(arr); //берем в переменную размер массива, чтобы всего 1 раз его взять, а не вызывать каждый раз в for
	cout << "Array is: ";
	for (size_t i = 0; i < size; i++) { //перебор
		cout << array_get(arr, i) << " "; //печать массива
	}
	cout << endl;
}

void task1(Array* arr)
{
	size_t size = array_size(arr); //узнаем длинну массива
	print(arr); //печатаем массив, чтобы можно было проверить программу
	int counter_two = 0, counter_five = 0; //два счетчика
	for (size_t i = 0; i < size; i++) { //перебор элементов
		Data elem = array_get(arr, i); //т.к. мы проверяем в 2 if, то берем в переменную, чтобы найти только 1 раз
		if (elem % 2 == 0) {
			counter_two++;
		}
		if (elem % 10 == 5) {
			counter_five++;
		}
	}
	cout << "Elements are even: " << counter_two << endl;
	cout << "Elements ending with 5" << counter_five << endl;
}

void task2(Array* arr)
{
	size_t size = array_size(arr); //узнаем длинну массива
	print(arr); //печатаем массив
	int total_count = 0; //счетчик, для элемента, который не делится ни на один другой элемент
	for (size_t i = 0; i < size; i++) { //перебор массива
		Data elem = array_get(arr, i); //узнаем элемент, который будем проверять
		size_t local_count = 0; //счетчик, если элемент не делится на другой 1 элемент массива
		for (size_t j = 0; j < size; j++) { //перебор массива второй раз
			if (elem % array_get(arr, j) != 0) { //проверяем, если элемент не делится на другой элемент массива, добавляем в local_count 1
				local_count += 1;
			}
		}
		if (local_count == size - 1) { //если элемент не делится ни на один другой элемент массива, то он не делится на (кол-во всех элементов)-(сам элемент)
			total_count += 1;
		}
	}
	cout << total_count;
}

int main()
{
	srand(time(NULL));
	Array* arr = NULL;
	cout << "Task 1" << endl;
	create(arr);
	task1(arr);
	array_delete(arr);
	cout << "Task 1" << endl;
	create(arr);
	task2(arr);
	array_delete(arr);
}
