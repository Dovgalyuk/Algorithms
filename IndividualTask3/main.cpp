#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

struct xy_coords
{
	size_t x, y;
};

void boarders_search(const char* filename, xy_coords& boarders)
{
	ifstream file(filename);
	if (!file.is_open())
		return;

	boarders = { 0, 0 };
	string str;

	while (getline(file, str))
	{
		if (boarders.x == 0)
			boarders.x = str.length();
		boarders.y += 1;
	}

	file.close();
}

char** lab_matrix_create(const char* filename, const xy_coords boarders, xy_coords& initial_vertex)
{
	ifstream file(filename);
	if (!file.is_open())
		return nullptr;

	char** lab_matrix = new char* [boarders.y];
	xy_coords xy = { 0, 0 };
	string str;

	for (; xy.y < boarders.y; xy.y++)
	{
		lab_matrix[xy.y] = new char[boarders.x];

		getline(file, str);

		for (xy.x = 0; xy.x < boarders.x; xy.x++)
		{
			if (str[xy.x] == 'X')
				initial_vertex = { xy.x, xy.y };

			lab_matrix[xy.y][xy.x] = str[xy.x];
		}
	}

	file.close();

	return lab_matrix;
}

void lab_matrix_print(char** lab_matrix, const xy_coords boarders)
{
	xy_coords temp = { 0, 0 };

	for (; temp.y < boarders.y; temp.y++)
	{
		for (temp.x = 0; temp.x < boarders.x; temp.x++)
			cout << lab_matrix[temp.y][temp.x];
		cout << endl;
	}
}

void lab_matrix_delete(char** lab_matrix, const xy_coords boarders)
{
	for (size_t y = 0; y < boarders.y; y++)
		delete[] lab_matrix[y];
	delete[] lab_matrix;
}

void bfs_check(char** lab_matrix, Queue* x_q, Queue* y_q, const xy_coords boarders, size_t& vertex_amount)
{
	xy_coords vertex = { queue_get(x_q), queue_get(y_q) };
	queue_remove(x_q);
	queue_remove(y_q);

	lab_matrix[vertex.y][vertex.x] = 'x';
	
	if (vertex.y - 1 >= 0)
		if (lab_matrix[vertex.y - 1][vertex.x] == '.') //up
		{
			vertex_amount += 1;
			queue_insert(x_q, vertex.x);
			queue_insert(y_q, vertex.y - 1);
		}

	if (vertex.x - 1 >= 0)
		if (lab_matrix[vertex.y][vertex.x - 1] == '.') //left
		{
			vertex_amount += 1;
			queue_insert(x_q, vertex.x - 1);
			queue_insert(y_q, vertex.y);
		}

	if (vertex.y + 1 < boarders.y)
		if (lab_matrix[vertex.y + 1][vertex.x] == '.') //down
		{
			vertex_amount += 1;
			queue_insert(x_q, vertex.x);
			queue_insert(y_q, vertex.y + 1);
		}

	if (vertex.x + 1 < boarders.x)
		if (lab_matrix[vertex.y][vertex.x + 1] == '.') //right
		{
			vertex_amount += 1;
			queue_insert(x_q, vertex.x + 1);
			queue_insert(y_q, vertex.y);
		}
}

void bfs_algorithm(char** lab_matrix, const xy_coords initial_vertex, const xy_coords boarders)
{
	size_t vertex_amount = 0;

	Queue* x_q = queue_create();
	Queue* y_q = queue_create();

	queue_insert(x_q, initial_vertex.x);
	queue_insert(y_q, initial_vertex.y);

	while (!queue_empty(y_q) && !queue_empty(x_q))
		bfs_check(lab_matrix, x_q, y_q, boarders, vertex_amount);

	queue_delete(x_q);
	queue_delete(y_q);

	cout << vertex_amount << endl;
	cout << endl;
}

int main()
{
	const char* filename = "F:\\Labyrinth.txt";
	xy_coords initial_vertex, boarders;
	initial_vertex = boarders = { 0, 0 };

	boarders_search(filename, boarders);
	char** lab_matrix = lab_matrix_create(filename, boarders, initial_vertex);

	if (lab_matrix != nullptr)
	{
		bfs_algorithm(lab_matrix, initial_vertex, boarders);
		lab_matrix_print(lab_matrix, boarders);
		lab_matrix_delete(lab_matrix, boarders);
	}

	return 0;
}