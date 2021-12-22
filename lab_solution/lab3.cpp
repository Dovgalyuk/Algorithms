#include <iostream>
#include "queue.h"

using namespace std;

const unsigned LETTERS = 26;
const unsigned ascii = 'A'; 
char paths[LETTERS][LETTERS]{};

int main()
{
	cout << "Enter the vertex: " << endl;

	char vertex;
	cin >> vertex;
	vertex -= ascii;
	
	cout << "Enter reactions or '....' to end: " << endl;
	
	char symbols, second_element, first_element = 0;
	while (first_element!= '.')
	{
		cin >> first_element >> symbols >> symbols >> second_element;
		if (isalpha(first_element)) {
			first_element -= ascii; //get the ordinal number of a letter in the alphabet
			second_element -= ascii;
			paths[first_element][second_element] = 1;
		}
	}

	//arr of visited vertexes
	bool* visited_vertex = new bool[LETTERS];
	for (int i = 0; i < LETTERS; i++)
	{
		visited_vertex[i] = false;
	}

	//bfs algorithm
	visited_vertex[vertex] = 0; //so that the first vertex is not counted
	Queue* queue = queue_create();
	queue_insert(queue, vertex);
	while (!queue_empty(queue))
	{
		Data curr_vertex = queue_get(queue);
		queue_remove(queue);
		for (int i = 0; i < LETTERS; i++)
		{
			if ((!visited_vertex[i]) && (paths[curr_vertex][i])) //add all neighboring vertices to the queue
			{
				queue_insert(queue, i);
				visited_vertex[i] = true;
			}
		}
	}

	for (int i = 0; i < LETTERS; i++)
	{
		if (visited_vertex[i])
		{
			cout << char(i + ascii) << " ";
		}
	}
	queue_delete(queue);
}