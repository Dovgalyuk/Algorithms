#include <iostream>
#include <string>
#include <fstream> 
#include "queue.h"

using std::cin; using std::cout; using std::string;  using std::ifstream;

int main()
{
	Queue* queue = queue_create();
	int width, height = 0, distance = 0, X, Y, z = 0;
	bool flag = true;
	string Patch, Str, BufStr;

	cout << "\n\tEnter the full path to the file: "; getline(cin, Patch); cout << "\n\n"; // Ввод пути к файлу с лабиринтом. У меня лежал тут ( C:\Users\ygali\Downloads\Labirint.txt )
	ifstream file(Patch);                                                        // Открываем файл на чтение

	if (!file.is_open())                                                          // Если файл НЕ открыт,
	{
		cout << "\n\tMistake! The path  ( " << Patch << " )  is not found!\n\n\a"; // Выводим сообщение об ошибке
                return 0;                                                
	}
	else                                                          
	{
		while (!file.eof())                                                    // Пока не достигли конца файла
		{
			getline(file, BufStr);                                           // Читаем файл в файл в буферную строку
			++height;                                                       // Считаем высоту лабиринта
			for (int i = 0; i < BufStr.size(); i++)                         // Записываем элементы лабиринта из буферной строки в выходящую      
			{                                                            // P.S. я не знаю почему, но простые способы записи из файла в строку у меня рботали до конца первой строчки лабиринта (######)
				if (!isdigit(BufStr[i]))                                // Поэтому пришлось выдумывать свой цикл... Зато рабочий :)
				{
					Str += BufStr[i];
					if (i == BufStr.size())
					{
						Str += '\n';
					}
				}
				else
				{
					Str += BufStr[i];

				}

			}
		}
		cout << "\tA maze in the form of a string: " << Str << "\n\n";  // Получаем нашь лабирит в виде строки
	}

	width = BufStr.size();                                            // Ширина лабиринта = размеру любой из его строк
	cout << "\tWidth: " << width << "\tHeight: " << height << "\n\n";
	file.close();                                                     // Закрываем файл
	BufStr.clear();                                                 // Чистим буферную строку

	string** maze = new string * [height];                         // Создаем двумерный масиив строк (матрицу) для лабиринта (При дебаге кода легко отслеживать текущее местоположение в лабиринте и запоминать уже посещенные места)
	for (int i = 0; i < height; i++)
	{
		maze[i] = new string[width];
	}


	bool** mark = new bool* [height];                            // Создаем двумерный булевый массив для фиксации уже посещенных мест     
	for (int i = 0; i < height; i++)
	{
		mark[i] = new bool[width];
		for (int j = 0; j < width; j++)
		{
			mark[i][j] = false;                               // и заполняем его false (0), ведь изначально мы нигде еще не были 
		}
	}

	for (int i = 0; i < height; i++)                     
	{
		for (int j = 0; j < width; j++)
		{
			maze[i][j] = Str[z];                            // Переносим все элементы лабиринта (который сейчас в виде строки Str) в двумерный массив строк (матрицу) maze[i][j]

			if (Str[z] == 'X')                             // Находим стартовую позицию в лабиринте
			{
				queue_insert(queue, i);
				queue_insert(queue, j);
			}
	              ++z;
		}
	}

	while (!queue_empty(queue))       // Пока очередь НЕ пуста
	{                                                                            
		X = queue_get(queue);      // Берем из очереди элемент (наимен строки)
		queue_remove(queue);       // Удаляем взятый элемент из очереди
		Y = queue_get(queue);       // Берем следующий элемент в очереди
		queue_remove(queue);      // Удаляем взятый элемент из очереди
		mark[X][Y] = true;       // Помечаем текущее местоположение как посещенное
		                                                                              // Пока flag = true и в текщем месте НЕ '.' (в которую можно попасть), НЕ '#' и НЕ 'X' (старт), а искомое число, которое располагается ближе всего к старту
		while (flag && maze[X][Y] != "." && (maze[X][Y] != "#") && (maze[X][Y] != "X" ))
		{
			cout << "\tThe shortest number found: " << maze[X][Y] << "\n";              // Печатаем это число
			flag = false;                                                     // Меняем flag на false, чтобы выйти из цикла
		}
		 // Если место в которое мы хотим попасть доступно или если это искомое число (хочу пометить позицию искомого числа как посещенное место)
		if (maze[X - 1][Y] == "." || maze[X - 1][Y] != "." && (maze[X - 1][Y] != "#") && (maze[X - 1][Y] != "X")) // Вверх в лабиринте
		{  
			if (mark[X - 1][Y] == false)       // Если мы еще не были в этом месте
			{
				mark[X - 1][Y] = true;        // Помечаем его как посещенное
				queue_insert(queue, X - 1);  // Заносим его координаты, чтобы
				queue_insert(queue, Y);     // далее его посетить 
				++distance;                // Считаем пройденный путь
			}
		}      // Для остальных направлений движения по лабиринту все аналогично

		if (maze[X + 1][Y] == "." || maze[X + 1][Y] != "." && (maze[X + 1][Y] != "#") && (maze[X + 1][Y] != "X")) {    // Вниз в лабиринте
			if (mark[X + 1][Y] == false)
			{
				mark[X + 1][Y] = true;
				queue_insert(queue, X + 1);
				queue_insert(queue, Y);
				++distance;
			}
		}

		if (maze[X][Y + 1] == "." || maze[X][Y + 1] != "." && (maze[X][Y + 1] != "#") && (maze[X][Y + 1] != "X")) {    // Вправо в лабиринте
			if (mark[X][Y + 1] == false)
			{
				mark[X][Y + 1] = true;
				queue_insert(queue, X);
				queue_insert(queue, Y + 1);
				++distance;
			}
		}

		if (maze[X][Y - 1] == "." || maze[X][Y + 1] != "." && (maze[X][Y + 1] != "#") && (maze[X][Y + 1] != "X")) {    // Влево в лабиринте
			if (mark[X][Y - 1] == false)
			{
				mark[X][Y - 1] = true;
				queue_insert(queue, X);
				queue_insert(queue, Y - 1);
				++distance;
			}
		}
	}
	cout << "\n\tA complete bypass of all available (not counting the start) cells took: " << distance << "\n";  // Выводим количество посещенных доступных (кроме старта) мест на экран
	cout << "\n\tMaze:\tVisited places in the maze:\n\n\n\t";

	for (int i = 0; i < height; i++)                   // Выводим матрицу лабиринта и посещенных мест на экран
	{
		for (int j = 0; j < width; j++)
		{
			cout << maze[i][j];
		}
		cout << "\t\t";
		for (int j = 0; j < width; j++)
		{
			cout << mark[i][j];
		}
		cout << "\n\t";
	}

	for (int i = 0; i < height; i++)              // Тут чистим созданные ранее динамические массивы
	{
		delete[] maze[i];
		delete[] mark[i];
	}
	delete[] maze;
	maze = nullptr;
	delete[] mark;
	mark = nullptr;

	queue_delete(queue);            // Удаляем очередь
	cout << "\n\n";
}
