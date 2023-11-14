#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono> // Библиотека для работы с временем
#include "hash.h" // Подключение заголовочного файла для пользовательской хеш-таблицы

using namespace std;

// Массив символов, используемых для генерации случайных слов
const char symbols[] = { "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" };

// Функция для генерации случайного слова
string random_word() {
	int size = rand() % 10 + 1; // Случайный размер слова от 1 до 10 символов
	string str;
	for (int i = 0; i < size; i++) str.push_back(symbols[rand() % 62]); // Генерация слова
	return str;
}

// Функция для тестирования хеш-таблицы
void execute(HashTable* table, int size) {
	unordered_map<string, string> map; // Стандартная хеш-таблица из STL

	// Переменные для измерения времени
	chrono::system_clock::time_point start_table;
	chrono::system_clock::time_point table_end;
	chrono::system_clock::time_point start_map;
	chrono::system_clock::time_point map_end;

	chrono::duration<double> time_table; // Время выполнения для пользовательской хеш-таблицы
	chrono::duration<double> time_map; // Время выполнения для unordered_map

	// Создание массивов для случайных ключей и значений
	string* random_value = new string[size];
	string* random_key = new string[size];

	// Заполнение массивов случайными словами
	for (int i = 0; i < size; i++) random_value[i] = random_word();
	for (int i = 0; i < size; i++) random_key[i] = random_word();

	// Тестирование пользовательской хеш-таблицы
	start_table = chrono::system_clock::now();
	for (int i = 0; i < size; i++) table->add(random_key[i], random_value[i]);
	table_end = chrono::system_clock::now();
	time_table = table_end - start_table;

	// Тестирование unordered_map
	start_map = chrono::system_clock::now();
	for (int i = 0; i < size; i++) map[random_key[i]] = random_value[i];
	map_end = chrono::system_clock::now();
	time_map = map_end - start_map;

	// Вывод результатов тестирования
	cout << "Added " << size << " elements. My table is " << time_table.count() << ". Unordered_map is " << time_map.count() << ".\n";

	// Освобождение памяти, занятой массивами ключей и значений
	delete[] random_key;
	delete[] random_value;
}

// Главная функция программы
int main() {
	setlocale(LC_ALL, "rus"); // Установка русской локализации
	srand((unsigned int)time(NULL)); // Инициализация генератора случайных чисел

	// Создание экземпляра пользовательской хеш-таблицы
	HashTable* table = new HashTable();

	// Выполнение тестирования для различного количества элементов
	execute(table, 100);
	execute(table, 500);
	execute(table, 1000);
	execute(table, 5000);
	execute(table, 10000);
	execute(table, 50000);
	execute(table, 100000);
	execute(table, 500000);

	// Освобождение памяти, занятой хеш-таблицей
	delete table;


	//HashTable* table2 = new HashTable();
	//table2->add("@","1");
	//table2->add("P", "2");
	//table2->del("@");
	//cout<<(table2->find("P").second)<<endl;

	return 0;
}