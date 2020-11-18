#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"

using namespace std;

struct xy_coords
{
	size_t x, y;
};

struct adj_coords
{
	bool up_correct;
	bool down_correct;
	bool left_correct;
	bool right_correct;
	xy_coords up;
	xy_coords down;
	xy_coords left;
	xy_coords right;
};

struct vertex_data
{
	char value;
	bool passed;
	adj_coords adj_listitem;
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

void adj_list_create(vertex_data** lab_matrix, const xy_coords boarders)
{
	xy_coords temp = { 0, 0 };
	
	for (; temp.y < boarders.y; temp.y++)
	{
		for (temp.x = 0; temp.x < boarders.x; temp.x++)
		{
			if (temp.y != 0)
			{
				lab_matrix[temp.y][temp.x].adj_listitem.up_correct = true;
				lab_matrix[temp.y][temp.x].adj_listitem.up = { temp.x, temp.y - 1 };
			}
			else
				lab_matrix[temp.y][temp.x].adj_listitem.up_correct = false;

			if (temp.y != boarders.y - 1)
			{
				lab_matrix[temp.y][temp.x].adj_listitem.down_correct = true;
				lab_matrix[temp.y][temp.x].adj_listitem.down = { temp.x, temp.y + 1 };
			}
			else
				lab_matrix[temp.y][temp.x].adj_listitem.down_correct = false;
			
			if (temp.x != 0)
			{
				lab_matrix[temp.y][temp.x].adj_listitem.left_correct = true;
				lab_matrix[temp.y][temp.x].adj_listitem.left = { temp.x - 1, temp.y };
			}
			else
				lab_matrix[temp.y][temp.x].adj_listitem.left_correct = false;

			if (temp.x != boarders.x - 1)
			{
				lab_matrix[temp.y][temp.x].adj_listitem.left_correct = true;
				lab_matrix[temp.y][temp.x].adj_listitem.right = { temp.x + 1, temp.y };
			}
			else
				lab_matrix[temp.y][temp.x].adj_listitem.right_correct = false;
		}
	}
}

vertex_data** vertex_matrix_create(const char* filename, const xy_coords boarders, xy_coords& initial_vertex)
{
	vertex_data** lab_matrix = new vertex_data * [boarders.y];
	xy_coords xy = { 0, 0 };

	ifstream file(filename);
	if (!file.is_open())
		return nullptr;

	string str;

	for (; xy.y < boarders.y; xy.y++)
	{
		lab_matrix[xy.y] = new vertex_data[boarders.x];
		
		getline(file, str);

		for (xy.x = 0; xy.x < boarders.x; xy.x++)
		{
			if (str[xy.x] == 'X')
				initial_vertex = { xy.x, xy.y };

			lab_matrix[xy.y][xy.x].value = str[xy.x];
			lab_matrix[xy.y][xy.x].passed = false;
		}
	}

	file.close();

	adj_list_create(lab_matrix, boarders);

	return lab_matrix;
}

void lab_matrix_print(vertex_data** lab_matrix, const xy_coords boarders)
{
	xy_coords temp = { 0, 0 };

	for (; temp.y < boarders.y; temp.y++)
	{
		for (temp.x = 0; temp.x < boarders.x; temp.x++)
			cout << lab_matrix[temp.y][temp.x].value;
		cout << endl;
	}
}

void lab_matrix_delete(vertex_data** lab_matrix, const xy_coords boarders)
{
	for (size_t y = 0; y < boarders.y; y++)
		delete[] lab_matrix[y];
	delete[] lab_matrix;
}

size_t coords_to_number(const xy_coords vertex, const xy_coords boarders)
{
	return vertex.y * boarders.x + vertex.x;
}

xy_coords number_to_coords(const size_t number, const xy_coords boarders)
{
	size_t y = number / boarders.x;
	return { number - boarders.x * y, y };
}

void bfs_check_sp(vertex_data** lab_matrix, Queue* queue, const xy_coords boarders, size_t& vertex_amount, const xy_coords temp)
{
	if (!lab_matrix[temp.y][temp.x].passed)
	{
		if (lab_matrix[temp.y][temp.x].value == '#')
			lab_matrix[temp.y][temp.x].passed = true;

		if (lab_matrix[temp.y][temp.x].value == '.')
		{
			vertex_amount += 1;
			queue_insert(queue, coords_to_number(temp, boarders));
		}
	}
}

void bfs_check_mp(vertex_data** lab_matrix, Queue* queue, const xy_coords boarders, size_t& vertex_amount)
{	
	xy_coords vertex = number_to_coords(queue_get(queue), boarders);
	queue_remove(queue);

	lab_matrix[vertex.y][vertex.x].passed = true;
	lab_matrix[vertex.y][vertex.x].value = 'x';

	if (lab_matrix[vertex.y][vertex.x].adj_listitem.up_correct)
	{
		xy_coords temp = lab_matrix[vertex.y][vertex.x].adj_listitem.up;
		bfs_check_sp(lab_matrix, queue, boarders, vertex_amount, temp);
	}

	if (lab_matrix[vertex.y][vertex.x].adj_listitem.down_correct)
	{
		xy_coords temp = lab_matrix[vertex.y][vertex.x].adj_listitem.down;
		bfs_check_sp(lab_matrix, queue, boarders, vertex_amount, temp);
	}

	if (lab_matrix[vertex.y][vertex.x].adj_listitem.left_correct)
	{
		xy_coords temp = lab_matrix[vertex.y][vertex.x].adj_listitem.left;
		bfs_check_sp(lab_matrix, queue, boarders, vertex_amount, temp);
	}
	
	if (lab_matrix[vertex.y][vertex.x].adj_listitem.right_correct)
	{
		xy_coords temp = lab_matrix[vertex.y][vertex.x].adj_listitem.right;
		bfs_check_sp(lab_matrix, queue, boarders, vertex_amount, temp);
	}
}

void bfs_algorithm(vertex_data** lab_matrix, const xy_coords initial_vertex, const xy_coords boarders)
{
	size_t vertex_amount = 0;

	Queue* queue = queue_create();
	queue_insert(queue, coords_to_number(initial_vertex, boarders));

	while (!queue_empty(queue))
		bfs_check_mp(lab_matrix, queue, boarders, vertex_amount);

	queue_delete(queue);

	cout << endl;
	cout << vertex_amount << endl;
}

int main()
{
	const char* filename = "F:\\Labyrinth.txt";
	xy_coords boarders, initial_vertex;
	boarders = initial_vertex = { 0, 0 };

	boarders_search(filename, boarders);

	vertex_data** lab_matrix = vertex_matrix_create(filename, boarders, initial_vertex);

	bfs_algorithm(lab_matrix, initial_vertex, boarders);

	lab_matrix_print(lab_matrix, boarders);

	lab_matrix_delete(lab_matrix, boarders);

	return 0;
}