/*
Реализовать контейнер - динамический массив array с неизменяемым размером (на любом из языков)
Проверить работу соответствующей тестовой программы
Написать две функции для обработки массива из следующих пунктов и вызвать их из функции main.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами.
Нечетные элементы массива уменьшить на m, а элементы с нечетными номерами увеличить на n. m и n ввести с клавиатуры.
Ввести целое число с клавиатуры, создать массив такой размерности и заполнить его случайными числами.
В массиве найти элементы, которые в нем встречаются только один раз, и вывести их на экран.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class DynamicArray {
public:
	int size;
	int* arr;

	DynamicArray(int s) {
		size = s;
		arr = new int[size];
	}

	void fillArrayRandomly() {
		for (int i = 0; i < size; i++) {
			arr[i] = rand() % 100 + 1; // Заполняем массив случайными числами от 1 до 100
		}
	}

	void printArray() {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void increaseOddIndicesByN(int n) {
		for (int i = 0; i < size; i++) {
			if (i % 2 != 0) {
				arr[i] += n;
			}
		}
	}

	void decreaseOddElementsByM(int m) {
		for (int i = 0; i < size; i++) {
			if (arr[i] % 2 != 0) {
				arr[i] -= m;
			}
		}
	}

	void findUniqueElements() {
		for (int i = 0; i < size; i++) {
			int count = 0;
			for (int j = 0; j < size; j++) {
				if (i != j && arr[i] == arr[j]) {
					count++;
				}
			}
			if (count == 0) {
				cout << arr[i] << " ";
			}
		}
	}

	~DynamicArray() {
		delete[] arr;
	}
};

int main() {
	setlocale(LC_ALL, "Ru");
	int size, n, m;
	srand(time(NULL)); // Инициализация функции rand()

	cout << "Введите размер массива: ";
	cin >> size;

	DynamicArray array(size);
	array.fillArrayRandomly();

	cout << "Случайный массив: ";
	array.printArray();

	cout << "Введите значение n: ";
	cin >> n;
	array.increaseOddIndicesByN(n);

	cout << "Введите значение m: ";
	cin >> m;
	array.decreaseOddElementsByM(m);

	cout << "Измененный массив: ";
	array.printArray();

	cout << "Элементы, встречающиеся только один раз: ";
	array.findUniqueElements();

	return 0;
}