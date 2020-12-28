#include <iostream>
#include "queue.h"


int main() 
{
	Queue* queue = queue_create();
	int x, y, iterator = 1;
	int sizeX, sizeY;

	std::cout << "What size will the sides of the maze be ? \n";
	std::cout << "sizeX: "; std::cin >> sizeX;
	std::cout << "sizeY: "; std::cin >> sizeY;
	
	char **maze = new char*[sizeX];
	for (int i = 0; i < sizeX; i++)
		maze[i] = new char[sizeY];

	for (int i = 0; i < sizeX; i++) {               /*Filling the array and finding X*/
		for (int j = 0; j < sizeY; j++) {
			std::cin >> maze[i][j];
			if (maze[i][j] == 'X') {
				queue_insert(queue, i);
				queue_insert(queue, j);
			}
		}
	}
	std::cout << std::endl;

	while(!queue_empty(queue))
	{
		x = queue_get(queue);
		queue_remove(queue);
		y = queue_get(queue);
		queue_remove(queue);
		
		
		if (maze[x][y + 1] == '.') {    //right
			queue_insert(queue, x);
			queue_insert(queue, y + 1);
			maze[x][y + 1] = 'X';
			iterator++;
		}
		if (maze[x][y - 1] == '.') {    //left
			queue_insert(queue, x);
			queue_insert(queue, y - 1);
			maze[x][y - 1] = 'X';
			iterator++;
		}
		if (maze[x + 1][y] == '.') {    //down
			queue_insert(queue, x + 1);
			queue_insert(queue, y);
			maze[x + 1][y] = 'X';
			iterator++;
		}
		if (maze[x - 1][y] == '.') {    //up
			queue_insert(queue, x - 1);
			queue_insert(queue, y);
			maze[x - 1][y] = 'X';
			iterator++;
		}
	}
	std::cout << iterator << std::endl;
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			std::cout << maze[i][j];
		}
		std::cout << std::endl;
	}
	
	queue_delete(queue);

	system("pause");
}

