#include <stdlib.h>
#include <iostream>
#include "orGraph.h"
#include <vector>

struct Graph {
	size_t keyofelements = 0;
	
	int **map; 
	
	int *element;

	


		   Graph(int a)
		   {
			   
			   keyofelements = a;
			   map = new int*[a];
			   for (int i = 0; i < a; ++i) 
				{
				   map[i] = new int[a];
				}
			   element = new int[a];
		   }

		    
		   ~Graph()
		   {
			   
			   for (int i = 0; i < keyofelements; ++i)
			   {
				   delete[]  map[i];
			   }

			   delete[] map;
			   delete[] element;
		   }

};

// создание пустого графа
Graph * graph_create() 
{
	Graph * myGraph = new Graph(0);
	return myGraph;
};

Graph * graph_create(int key) 
{
	Graph * myGraph = new Graph(key);
	return myGraph;
};

// удаление графа
void  graph_delete(Graph * graph) 
{
	delete graph;
};

// включение ребра в граф
void  graph_insert_reb(Graph * graph, int num1,int num2,int weight)
{
	graph->map[num1 - 1][num2 - 1] = weight;
};

// удаление ребра из графа
void graph_remove_reb(Graph * graph, int num1, int num2) 
{
	graph->map[num1 - 1][num2 - 1] = 0;
};
// размер графа
int graph_size(Graph * graph) 
{
	return graph->keyofelements;
}
//включение вершины в граф
void graph_insert_ver(Graph * graph, int data)
{
	int key = graph->keyofelements; // копия колка элементов
	
									
	// новая карта
	 int ** newmap; 
	*newmap = new  int[key + 1];
	//новое колво элементов
	 int * newelement = new  int[key+1];

	 
	for (int i = 0; i < key+1; ++i)
	{
		newmap[i] = new  int[key];
	}
	newelement = new  int[key+1];

	//копирование
	for (int i = 0; i < key; ++i) 
	{
		for (int j = 0; j < key; ++j)
		{
			newmap[i][j] = graph->map[i][j];
		}
	}

	//последний элемент
		for (int j = 0; j < key+1; ++j)
		{
			newmap[key][j] = 0;
		}
		for (int j = 0; j < key+1; ++j)
		{
			newmap[j][key] = 0;
		}



	for (int i = 0; i < key; ++i) 
	{
		newelement[i] = graph->element[i];
		
	}
		newelement[key + 1] = data;

		delete[] graph->element;
		for (int i = 0; i < key; ++i) 
		{
			delete[] graph->map[i];
		}
		delete[] graph->map;


		graph->element = newelement;
		graph->map = newmap;
		graph->keyofelements = key + 1;

}
//удаление вершины из графа 
void graph_remove_ver(Graph *graph, int num) 
{
	for (int i = 0; i < graph->keyofelements; ++i) 
	{
		graph->map[i][num] = -1;
	}
	for (int i = 0; i < graph->keyofelements; ++i)
	{
		graph->map[num][i] = -1;
	}
	
	graph->element[num] = -1;


	int key = graph->keyofelements;

	 int ** newmap;
	*newmap = new  int[key + 1];
	 int * newelement = new  int[key + 1];

	for (int i = 0; i < key - 1; ++i)
	{
		newmap[i] = new  int[key];
	}
	newelement = new  int[key - 1];
	

	//копирование карты в новый массив
	int bufi = 0;
	while (bufi  != (key - 1))
	{
		int bufkey = 0;
		if (graph->map[bufkey][0] == -1) 
		{
			if (bufkey + 1 <= graph->keyofelements) 
			{
				bufkey++; 
			}
			else 
			{
				break;

			}
		}
		else 
		{
			newmap[bufi] = graph->map[bufkey];
			bufi++;
			bufkey++;
		}
	}

	
	for (int i = 0; i < key; i++) 
	{
		int j = 0;
		if (graph->element[i] != -1) 
		{
			newelement[j] = graph->element[i];
			j++;
		}
	}
	
	graph->element = newelement;
	graph->map = newmap;
	graph->keyofelements = key - 1;


	delete[] graph->element;
	for (int i = 0; i < key; ++i)
	{
		delete[] graph->map[i];
	}
	delete[] graph->map;
}
//проверить, существует ли ребро между вершинами
bool graph_is_valid_rebro(Graph *graph, int ver1,int ver2) 
{
	if (graph->map[ver1][ver2] > 0)
		return 1;
	else
		return 0;

}
//пометка для ребра 
void graph_pometka_ver(Graph *graph, int ver, int data)
{
	graph->element[ver] = data;
}
// пометка для вершины
void graph_pometka_reb(Graph *graph, int rebx, int reby, int data)
{
	graph->map[rebx][reby] = data;
}
// получить пометку вершины
int graph_get_ver(Graph *graph,int vernum) 
{
	return graph->element[vernum];
}
//получить пометку ребра
int graph_get_reb(Graph *graph, int rebx,int reby) 
{
	return graph->map[rebx][reby];
}
// вывести матрицу графа
void show_graph(Graph *graph) 
{

	int n = graph_size(graph);

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cout << graph_get_reb(graph,i,j);
		}
		std::cout << std::endl;
	}
}