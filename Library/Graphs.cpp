#include "Graphs.h"
#include "array.h"

struct Graph
{
	Array* matrix;
	Array* mark_vertix;
	Array* mark_edge;
	int num;
};


Graph* graph_create(int num)
{
	Graph* a = new Graph;
	a->matrix = array_create(num*num);
	a->mark_edge = array_create(num * num);
	a->mark_vertix = array_create(num);
	a->num = num;
	for (int i = 0; i < num*num; i++)
	{
		array_set(a->matrix, i, 0);
		array_set(a->mark_edge, i, 0);
	}
	for (int i = 0; i < num; i++)
	{
		array_set(a->mark_vertix, i, 0);
	}
	return a;
}

void graph_delete(Graph* graph)
{
	array_delete(graph->matrix);
	array_delete(graph->mark_edge);
	array_delete(graph->mark_vertix);
	delete graph;
}

void add_vertex(Graph* graph)
{
	int size = array_size(graph->matrix);
	int new_size = (graph->num+1)* (graph->num + 1);
	Array* tmp1 = array_create(new_size);
	Array* tmp2 = array_create(new_size);
	Array* tmp3 = array_create(graph->num + 1);
	Array* mp1 = graph->matrix;
	Array* mp2 = graph->mark_edge;
	Array* mp3 = graph->mark_vertix;
	for (int i = 0; i < size; i++)
	{
		array_set(tmp1, i, array_get(graph->matrix, i));
		array_set(tmp2, i, array_get(graph->mark_edge, i));
	}
	for (int i = size; i < new_size; i++)
	{
		array_set(tmp1, i, 0);
		array_set(tmp2, i, 0);
	}
	for (int i = 0; i < graph->num; i++)
	{	
		array_set(tmp3, i, array_get(graph->mark_vertix, i));
	}
	array_set(tmp3, graph->num, 0);
	graph->num++;
	graph->matrix = tmp1;
	graph->mark_edge = tmp2;
	graph->mark_vertix = tmp3;
	array_delete(mp1);
	array_delete(mp2);
	array_delete(mp3);
}

void add_edge(Graph* graph, int f_v, int s_v)
{
	array_set(graph->matrix, (f_v-1) * graph->num + (s_v-1), 1);
}

void delete_vertex(Graph* graph, int num)
{
	int size = array_size(graph->matrix);
	int new_size = (graph->num - 1) * (graph->num - 1);
	Array* tmp1 = array_create(new_size);
	Array* tmp2 = array_create(new_size);
	Array* tmp3 = array_create(graph->num - 1);
	Array* mp1 = graph->matrix;
	Array* mp2 = graph->mark_edge;
	Array* mp3 = graph->mark_vertix;
	for (int i = 0; i < new_size; i++)
	{
		array_set(tmp1, i, array_get(graph->matrix, i));
		array_set(tmp2, i, array_get(graph->mark_edge, i));
	}
	for (int i = 0; i < graph->num-1; i++)
	{
		array_set(tmp3, i, array_get(graph->mark_vertix, i));
	}
	graph->num--;
	graph->matrix = tmp1;
	graph->mark_edge = tmp2;
	graph->mark_vertix = tmp3;
	array_delete(mp1);
	array_delete(mp2);
	array_delete(mp3);
}

void delete_edge(Graph* graph, int f_v, int s_v)
{
	array_set(graph->matrix, (f_v-1) * graph->num + (s_v-1), 0);
}

bool check_edge(Graph* graph, int f_v, int s_v)
{
	if (array_get(graph->matrix, (f_v-1) * graph->num + (s_v-1)) == 1)
		return true;
	else
		return false;
}

void add_mark_vertex(Graph* graph, int num, int mark)
{
	array_set(graph->mark_vertix, num, mark);
}

int read_mark_vertex(Graph* graph, int num)
{
	return array_get(graph->mark_vertix, num);
}

void add_mark_edge(Graph* graph, int f_v, int s_v, int mark)
{
	array_set(graph->mark_edge, (f_v - 1) * graph->num + (s_v - 1), mark);
}

int read_mark_edge(Graph* graph, int f_v, int s_v)
{
	return array_get(graph->mark_edge, (f_v-1) * graph->num + (s_v-1));
}
