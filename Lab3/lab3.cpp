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
	cout << "Íå çàáóäüòå óêàçàòü ðàñøèðåíèå ôàéëà! (.txt)" << endl;
	cout << "Ââåäèòå ïîëíûé ïóòü ê ôàéëó: ";
	getline(cin, s);
	// s = "C:\\Users\\Danya\\source\\repos\\Algorithms3\\Algorithms3\\inputfile.txt";
	ifstream input(s);
	if (!input.is_open())                                                
	{
		cout << "Ôàéë íå íàéäåí!" << endl;
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
			cout << "Êðàò÷àéøèé ïóòü: " << end_vertex;
		}
		for (int i = 0; i < count; i++)              // Òóò ÷èñòèì ñîçäàííûå ðàíåå äèíàìè÷åñêèå ìàññèâû
		{
			delete[] matrix[i];
		}
		delete[] matrix;
		matrix = nullptr;
		queue_delete(queue);
	}
}



	
