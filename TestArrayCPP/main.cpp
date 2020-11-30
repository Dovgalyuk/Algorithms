#include <iostream>
#include <fstream>
#include <locale>
#include "queue.h"
using namespace std;

//Функция чтения данных из файла
char** readFile(int &numCol, int &numRow) {
	numCol = 0, numRow = 0;
	int i = 0;
	char **labir = NULL;	//Инициализация двумерного массива для лабиринта
	string line;			//Строка, которая будет использоваться при чтении из файла
	ifstream in("input.txt");	//Входной файл
	if (in.is_open())	//Если файл удалось открыть
	{
		while (getline(in, line)) {	//Пробегаем файл для подсчета длины строки numRow
			numRow++;
		}
		numCol = line.size();	//Длина колонки
		labir = new char*[numRow];	//Выделяем память для лабиринта

		cout << "Размеры прямоугольника:" << numCol << '*' << numRow << endl;
		cout << "Вход:" << endl;
		in.clear();				//Сбрасываем in для повторного чтения файла
		in.seekg(0, ios::beg);	//
		//Считываем данные из файла и записываем в массив labir
		while (getline(in, line)) {
			labir[i] = new char[numCol];
			for (int j = 0; j < line.size(); j++) {
				labir[i][j] = line[j];
				cout << labir[i][j];
			}
			cout << endl;
			i++;
		}
	}
	else {
		cout << "Файл input.txt не найден или не удалось открыть." << endl;
	}
	in.close();	//Закрываем файл
	return labir;	//Возвращаем массив с лабиринтом в главную функцию main
}

//Функция нахождения кратчайшего пути с помощью волнового алгоритма
void findPath(bool &mark, int numCol, int numRow, char **labir, int **visited, int **path, queue &q) {
	int xStartX, yStartX, xEndY, yEndY;	//Координаты старта и финиша
	int x, y;	//Координаты выбранной клетки
	for (int i = 0; i < numRow; i++) {
		visited[i] = new int[numCol];	//Выделяем память для массива
		path[i] = new int[numCol];		//Выделяем память для массива
		for (int j = 0; j < numCol; j++) {
			visited[i][j] = 0;
			path[i][j] = -1;
			if (labir[i][j] == 'X') { /* находим начало пути*/
				xStartX = i;
				yStartX = j;
				q.push(i);  /* заносим начальную клетку */
				q.push(j);  /* в план посещения */
				path[i][j] = 1;
			}
			else if (labir[i][j] == 'Y') { /* находим конечную точку */
				xEndY = i;
				yEndY = j;
			}
		}
	}

	//Пока очередь посещения клеток
	while (q.empty() == false) {	//Пока очередь не пустая, делаем
		x = q.front();	//Берём координату x первого элемента очереди
		q.pop();		//Удаляем его из очереди
		y = q.front();	//Берём координату y первого элемента очереди
		q.pop();		//Удаляем его из очереди

		if (!visited[x][y]) {	//Если ещё не посетили данную клетку, то делаем для его соседних клеток
			//Проверяем не вышли ли за границу лабиринта, посещена ли соседняя клетка, можно ли пройти через него.
			if ((x + 1) < numRow && (x + 1) >= 0 && !visited[x + 1][y] &&
				(labir[x + 1][y] == '.' || labir[x + 1][y] == 'Y')) {
				path[x + 1][y] = path[x][y] + 1;
				q.push(x + 1);
				q.push(y);
			}
			if ((x - 1) < numRow && (x - 1) >= 0 && !visited[x - 1][y] &&
				(labir[x - 1][y] == '.' || labir[x - 1][y] == 'Y')) {
				path[x - 1][y] = path[x][y] + 1;
				q.push(x - 1);
				q.push(y);
			}
			if ((y + 1) < numRow && (y + 1) >= 0 && !visited[x][y + 1] &&
				(labir[x][y + 1] == '.' || labir[x][y + 1] == 'Y')) {
				path[x][y + 1] = path[x][y] + 1;
				q.push(x);
				q.push(y + 1);
			}
			if ((y - 1) < numRow && (y - 1) >= 0 && !visited[x][y - 1] &&
				(labir[x][y - 1] == '.' || labir[x][y - 1] == 'Y')) {
				path[x][y - 1] = path[x][y] + 1;
				q.push(x);
				q.push(y - 1);
			}
			visited[x][y] = 1;	//Отмечаем что побывали в данной клетке
		}

		if (visited[xEndY][yEndY]) {	//Если посетили финишную клетку
			mark = true;
			x = xEndY;	//x будет кординатой х фишиша Y
			y = yEndY;	//y будет кординатой y фишиша Y
			//Восстановление кратчайшего пути
			while (path[x][y] != 2) {
				if ((x - 1) >= 0 && (x - 1) < numRow && (path[x - 1][y] == path[x][y] - 1)) {
					x = x - 1;
					labir[x][y] = 'x';
				}
				else if ((x + 1) >= 0 && (x + 1) < numRow && (path[x + 1][y] == path[x][y] - 1)) {
					x = x + 1;
					labir[x][y] = 'x';
				}
				else if ((y - 1) >= 0 && (y - 1) < numRow && (path[x][y - 1] == path[x][y] - 1)) {
					y = y - 1;
					labir[x][y] = 'x';
				}
				else if ((y + 1) >= 0 && (y + 1) < numRow && (path[x][y + 1] == path[x][y] - 1)) {
					y = y + 1;
					labir[x][y] = 'x';
				}
			}
		}
	}
}

//Функция записи данных в файл
void writeFile(bool &mark, int &numCol, int &numRow, char **labir){
	ofstream out("output.txt");	//Выходной файл
	if (out.is_open())	//Если файл удалось открыть
	{
		cout << endl;
		cout << "Выход:" << endl;
		if (mark == true) {	//Путь существует
			//Записываем лабиринт из массива в файл
			for (int i = 0; i < numRow; i++) {
				for (int j = 0; j < numCol; j++) {
					out << labir[i][j];
					cout << labir[i][j];
				}
				out << endl;
				cout << endl;
			}
		}
		else {	//Путь не существует
			cout << "IMPOSSIBLE" << endl;
			out << "IMPOSSIBLE";
		}
	}
	out.close();
}

//ГЛАВНАЯ ФУНКЦИЯ
int main() {
	setlocale(LC_ALL, "Russian");	//Для вывода русских слов
	int numCol;	//Размер лабиринта: длина колонки
	int numRow;	//Размер лабиринта: длина ряда(строки)
	bool mark = false;	//Если true, то путь существует
	char **labir;	//Двумерный массив хранящий лабиринт
	int **visited;	//Двумерный массив хранящий посещенные клетки лабиринта
	int **path;		//Двумерный массив хранящий пути в лабиринте
	queue q;		//Очередь посещения клеток (поиска пути)

	//Функция чтения данных из файла. Оттуда получаем наш лабиринт в массив labir
	labir = readFile(numCol, numRow);
	
	visited = new int* [numRow];	//Выделяем память для массивов. Делаем их одномерными
	path = new int* [numRow];		//

	//Функция поиска кратчайшего пути
	findPath(mark, numCol, numRow, labir, visited, path, q);

	//Функция записи данных (преобразованного лабиринта) в файл. 
	writeFile(mark,numCol, numRow, labir);

	system("pause");
	return 0;
}