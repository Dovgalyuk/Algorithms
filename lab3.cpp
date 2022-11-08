#include <iostream>
#include <string>
#include <fstream>
#include "queue.h"

using std::cin; using std::cout; using std::string; using std::ifstream; using std::endl;

int main()
{
	setlocale(LC_ALL, "ru");
	Data count, start, end;
	string s;
	cout << "Не забудьте указать расширение файла! (.txt)" << endl;
	cout << "Введите полный путь к файлу: ";
	getline(cin, s);
	// s = "C:\\Users\\Danya\\source\\repos\\Algorithms3\\Algorithms3\\inputfile.txt";
	ifstream input(s);
	if (!input.is_open())                                                
	{
		cout << "Файл не найден!" << endl;
		system("pause");
		system("cls");
		return main();
	}
	else 
	{
		string getcontent;
		while (getline(input, getcontent))
		{
			cout << getcontent << endl;
		}
		ifstream input(s);
		input >> count >> start >> end;
		Data** matrix = new Data* [count];
		for (int i = 0; i < count; i++)
		{
			Data* str = new Data[count];
			for (int j = 0; j < count; j++)
			{
				input >> str[j];
			}
			matrix[i] = str;
		}
		input.close();
		start--, end--;
		Data* vertexes = new Data[count];
		for (int i = 0; i < count; i++)
		{
			vertexes[i] = -1;
		}
		vertexes[start] = 0;
		Queue* queue = queue_create();
		queue_insert(queue, start);
		while (!queue_empty(queue))
		{
			Data vertex = queue_get(queue);
			queue_remove(queue);
			for (int i = 0; i < count; i++)
			{
				if (vertexes[i] == -1 && matrix[vertex][i] == 1)
				{
					queue_insert(queue, i);
					vertexes[i] = vertexes[vertex] + 1;
				}
			}
		}
		Data end_vertex = vertexes[end];
		if (end_vertex == -1)
		{
			cout << "IMPOSSIBLE";
		}
		else
		{
			cout << "Кратчайший путь: " << end_vertex;
		}
		for (int i = 0; i < count; i++)              // Тут чистим созданные ранее динамические массивы
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
		queue_delete(queue);
	}
}



	