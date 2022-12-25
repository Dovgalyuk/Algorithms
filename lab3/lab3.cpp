#include <iostream>
#include <string>
#include <fstream> 
#include <cctype>
#include "queue.h"
#include "vector.h"

int main()
{
	setlocale(LC_ALL, "rus");
	Queue* queue = queue_create();
	int width, height = 0, x = 0, y = 0, z = 0;
	std::string way, str, buf;
	std::ifstream file;
	file.open("c:\\file.txt");

while (!file.eof())
{
	getline(file, buf);
	++height;
	str += buf;
}
	width = buf.size();
	file.close();
	buf.clear();
	int** mark = new int* [height];

	for (int i = 0; i < height; i++)
	{
		mark[i] = new int[width];
		for (int j = 0; j < width; j++)
			mark[i][j] = 0;
		
	}
	
	char**  labyrinth = new char* [height];
	for (int i = 0; i < height; i++)
	{
		labyrinth[i] = new char[width];
		for (int j = 0; j < width; j++)
		{
			labyrinth[i][j] = str[z];

			if (labyrinth[i][j] == 'X')
			{
				queue_insert(queue, i);
				queue_insert(queue, j);
				mark[i][j] = 1;
			}
			++z;
		}
	}

	while (!queue_empty(queue))
	{
		x = queue_get(queue);
		queue_remove(queue);
		y = queue_get(queue);
		queue_remove(queue);

		if ( (labyrinth[x - 1][y] == '.') || (isdigit(labyrinth[x-1][y])) )
		{
			if (mark[x - 1][y] == 0)
			{ 
				queue_insert(queue, x - 1);
				queue_insert(queue, y);
				mark[x - 1][y] = mark[x][y] + 1;
			}
				
		}
		if ( (labyrinth[x + 1][y] == '.') || (isdigit(labyrinth[x + 1][y])) )
		{
			if (mark[x + 1][y] == 0)
			{
				queue_insert(queue, x + 1);
				queue_insert(queue, y);
				mark[x + 1][y] = mark[x][y] + 1;
			}
		
		}

		if( (labyrinth[x][y + 1] == '.') || (isdigit(labyrinth[x][y+1])) )
		{
			if (mark[x][y + 1] == 0)
			{
                queue_insert(queue, x);
				queue_insert(queue, y + 1);
				mark[x][y + 1] = mark[x][y] + 1;
			}
		}

		if ((labyrinth[x][y - 1] == '.') || (isdigit(labyrinth[x][y-1])) )
		{
			if (mark[x][y - 1] == 0)
			{ 
				queue_insert(queue, x);
				queue_insert(queue, y - 1);
				mark[x][y - 1] = mark[x][y] + 1;
				
			}	
			
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << labyrinth[i][j];
		}
		std::cout << "\t";
		for (int j = 0; j < width; j++)
		{
			std::cout << mark[i][j];
		}
		std::cout << "\n";
	}
	int minway = 100;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((isdigit(labyrinth[i][j]))&&(mark[i][j]<minway))
					minway = mark[i][j];	
		
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (isdigit(labyrinth[i][j]) && (mark[i][j] == minway))
				std::cout <<"Ближайшая к стартовой позиции цифра: "<< labyrinth[i][j];
		}
	}


	for (int i = 0; i < height; i++)
	{
		delete[]  labyrinth[i];
		delete[] mark[i];
	}
	delete[]  labyrinth;
	labyrinth = nullptr;
	delete[] mark;
	mark = nullptr;
	queue_delete(queue);
	 
}
