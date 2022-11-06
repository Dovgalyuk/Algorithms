#include <iostream>
#include <string>
#include <fstream> 
#include "queue.h"

using namespace std;

int main()
{
	Queue* queue = queue_create();
	int width, height = 0, x = 0, y = 0, z = 0;
	string way, str, strbuf;

	cout << "Enter the way to the file: "; 
	getline(cin, way); 
	cout << "\n"; //C:\Users\User\Desktop\labirint.txt 
	ifstream file(way);

	if (!file.is_open())
	{
		cout << "\nMistake! The path  ( " << way << " )  is not found!\n";
		return 0;
	}
	else
	{
		while (!file.eof())
		{
			getline(file, strbuf);
			++height;
			str += strbuf;
		}
	}
	width = strbuf.size();
	file.close();
	strbuf.clear();
	bool** mark = new bool* [height];
	for (int i = 0; i < height; i++)
	{
		mark[i] = new bool[width];
		for (int j = 0; j < width; j++)
		{
			mark[i][j] = false;
		}
	}
	char** maze = new char* [height];
	for (int i = 0; i < height; i++)
	{
		maze[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			maze[i][j] = str[z];

			if (maze[i][j] == 'X')
			{
				queue_insert(queue, i);
				queue_insert(queue, j);
				mark[i][j] = true;
			}
			++z;
		}
	}
	int count = 1;
	while (!queue_empty(queue))
	{
		x = queue_get(queue);
		queue_remove(queue);
		y = queue_get(queue);
		queue_remove(queue);
		mark[x][y] = true;

		if (maze[x - 1][y] == '.')
		{
			if (mark[x - 1][y] == false)
			{
				queue_insert(queue, x - 1);
				queue_insert(queue, y);
				++count;
			}
		}
		if (maze[x + 1][y] == '.')
		{
			if (mark[x + 1][y] == false)
			{
				queue_insert(queue, x + 1);
				queue_insert(queue, y);
				++count;
			}
		}
		if (maze[x][y + 1] == '.')
		{
			if (mark[x][y + 1] == false)
			{
				queue_insert(queue, x);
				queue_insert(queue, y + 1);
				++count;
			}
		}
		if (maze[x][y - 1] == '.')
		{
			if (mark[x][y - 1] == false)
			{
				queue_insert(queue, x);
				queue_insert(queue, y - 1);
				++count;
			}
		}
	}
	cout << "Count visited places: " << count;
	cout << "\nVisited places: \n";
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << maze[i][j];
		}
		cout << "\t";
		for (int j = 0; j < width; j++)
		{
			if (mark[i][j] == 1)
				cout << "x";
			else
				cout << "#";
		}
		cout << "\n";
	}

	for (int i = 0; i < height; i++)
	{
		delete[] maze[i];
		delete[] mark[i];
	}
	delete[] maze;
	maze = nullptr;
	delete[] mark;
	mark = nullptr;
	queue_delete(queue);
}
