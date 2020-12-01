#include "queue.h"
#include <fstream>

using namespace std;

int main()
{
	const string input_path = "input";
	const string output_path = "output";

	ifstream fin;
	ofstream fout;

	fin.open(input_path + ".txt"); 
	fout.open(output_path + ".txt");
	if (!fin.is_open() || !fout.is_open())
	{
		fin.close();
		fout.close();
		return 0;
	}

	int graph_size;
	fin >> graph_size;

	bool** matrix = new bool* [graph_size];
	for (int i = 0; i < graph_size; i++)
	{
		matrix[i] = new bool[graph_size];
		for (int j = 0; j < graph_size; j++)
			fin >> matrix[i][j];
	}
	
	int* peak = new int[graph_size];
	for (int i = 0; i < graph_size; i++)
		peak[i] = graph_size;
	//значение graph_size используется в качестве обозначения не пройденых вершин
	//так как в графе всего graph_size вершин, то максимальное растояние в таком графе = graph_size -1

	Queue* queue =queue_create();

	peak[0] = 0;
	queue_insert(queue, 0);

	for(int node, path_len =1; ! queue_empty(queue); path_len++)
	{
		node =queue_get(queue);
		queue_remove(queue);
		for (int new_node = 0; new_node < graph_size; new_node++)
		{
			if (matrix[node][new_node] && peak[new_node] == graph_size)
			{
				peak[new_node] = path_len;
				queue_insert(queue, new_node);
			}
		}
	}

	for (int i = 0; i < graph_size; i++)
	{
		if (peak[i] == graph_size)
			fout << '-';
		else
			fout << peak[i];
		fout << ' ';
	}

	fin.close();
	fout.close();
	for (int i = 0; i < graph_size; i++)
		delete[] matrix[i];
	delete[] matrix;
	delete[] peak;
	queue_delete(queue);
}