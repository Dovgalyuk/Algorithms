//Попов Владимир 8091
//test
#include <iostream>
#include "queue.h"
#include "Graphs.h"

int main()
{
	Graph* a;
	a=graph_create(6);
	add_edge(a, 0, 1);
	add_mark_vertex(a, 0, 90);
	std::cout << (int)check_edge(a, 0, 1) << ' ' << read_mark_vertex(a, 0);
}