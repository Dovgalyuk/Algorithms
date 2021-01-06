#include <iostream>
#include "vector.h"
#include "queue.h"

using namespace std;

int main()
{
	Data count, start, end;
	cin >> count >> start >> end;

	Data** matrix = new Data*[count];
	
	
	for (int i = 0; i < count; i++)
	{
		Data* row = new Data[count];
		for (int j = 0; j < count; j++)
		{
			cin >> row[j];
		}
		matrix[i] = row;
	}
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
		cout << end_vertex;
	}
}