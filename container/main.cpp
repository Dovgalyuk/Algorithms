#define MAX_LEN_STRING 12

#include <clocale>
#include <iostream>
#include <fstream>
#include <ctime>
#include <set>
#include <string>

#include "interface.h"
#include "avltree.h"

using namespace std;

//Функция выполнения
void demoInterface(Interface &container) {
	cout << "ДЕМОНСТРАЦИЯ РАБОТЫ ИНТЕРФЕЙСА:" << endl;
	string s1 = "abcd";
	string s2 = "ef";
	string s3 = "xyz";
	string s4 = "hi";

	//Добавление строк
	container.addValue(&s1);
	cout << s1 << " добавлена." << endl;
	container.addValue(&s2);
	cout << s2 << " добавлена." << endl;
	container.addValue(&s3);
	cout << s3 << " добавлена." << endl;

	//Поиск строки
	if (container.findValue(&s4) == true)
		cout << s4 << " найдена." << endl;
	else
		cout << s4 << " не найдена в контейнере." << endl;

	if (container.findValue(&s1) == true)
		cout << s1 << " найдена." << endl;
	else
		cout << s1 << " не найдена в контейнере." << endl;


	//Удаление строк
	if (container.deleteValue(&s4) == true)
		cout << s4 << " удалена." << endl;
	else
		cout << s4 << " не удалена, так как нет в контейнере." << endl;

	if (container.deleteValue(&s2) == true)
		cout << s2 << " удалена." << endl;
	else
		cout << s2 << " не удалена, так как нет в контейнере." << endl;
}

//Генератор входных данных различного объема для нашего AVL контейнера и запись в файл
void generatorData() {
	srand((unsigned int)time(NULL));	//Начальная генерация
	int numString = rand() + 1;				//Количество строк. Случайное от 1 до 32768.
	int lenString;						//Длина текущей строки			
	ofstream out("InputData.txt");
	if (out.is_open()) {
		for (int i = 0;i < numString;i++) {
			lenString = rand() % MAX_LEN_STRING;
			for (int j = 0; j < lenString;j++) {
				out.put(rand() % 26 + 97);
			}
			out.put('\n');
		}
	}
	out.close();
}

//Чтение данных в контейнер
void readDataInContainer(Interface &container) {
	string str;
	ifstream in("InputData.txt");
	if (in.is_open())
	{
		clock_t start = clock();
		while (getline(in, str, '\n')) {
			container.addValue(&str);
		}
		clock_t finish = clock();
		cout << "Время добавление в созданный контейнер содержимого файла: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "Файл InputData.txt не найден или не удалось открыть." << endl;
	}
	in.close();
}

//Чтение данных в set
void readDataInSet(set <string> &containerSet) {
	//char *str = (char*)malloc(sizeof(char));
	string str;
	ifstream in("InputData.txt");
	if (in.is_open())
	{
		clock_t start = clock();
		//while (in.getline(str, MAX_LEN_STRING)) {
		while (getline(in, str)) {
			containerSet.insert(str);
			//char *str = (char*)malloc(sizeof(char));
		}
		clock_t finish = clock();
		cout << "Время добавление в контейнер set содержимого файла (сек): " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "Файл InputData.txt не найден или не удалось открыть." << endl;
	}
	in.close();
}

//ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "Russian");

	//1. Демонстрация работы интерфейса
	AVLTree container;
	demoInterface(container);

	//4. ГЕНЕРАТОР ВХОДНЫХ ДАННЫХ РАЗЛИЧНОГО ОБЪЕМА ДЛЯ НАШЕГО AVL КОНТЕЙНЕРА.
	cout << "СРАВНЕНИЕ СКОРОСТЕЙ ОПЕРАЦИИ ДОБАВЛЕНИЯ В КОНТЕЙНЕРЫ:" << endl;
	//4.1. Генерируем строки и записываем в файл
	generatorData();

	//4.2. Cкорость выполнения операции добавления в контейнер содержимого файла
	AVLTree container2;
	readDataInContainer(container2);

	//4.3. Cкорость выполнения операции добавления в контейнер std:set
	set <string> containerSet;
	readDataInSet(containerSet);

	system("pause");
	return 0;
}