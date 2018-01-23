#include "../Library/orGraph.h"
#include <iostream>
#include <vector>
#include <conio.h>
using namespace std;

int main() 
{
	Graph *p;

	p = graph_create(5);


	graph_insert_reb(p, 1, 1, 1);
	graph_insert_reb(p, 1, 2, 1);
	graph_insert_reb(p, 1, 3, 4);
	graph_insert_reb(p, 1, 4, 4);
	graph_insert_reb(p, 1, 5, 4);

	graph_insert_reb(p, 2, 1, 4);
	graph_insert_reb(p, 2, 2, 1);
	graph_insert_reb(p, 2, 3, 2);
	graph_insert_reb(p, 2, 4, 4);
	graph_insert_reb(p, 2, 5, 4);

	graph_insert_reb(p, 3, 1, 4);
	graph_insert_reb(p, 3, 2, 4);
	graph_insert_reb(p, 3, 3, 1);
	graph_insert_reb(p, 3, 4, 3);
	graph_insert_reb(p, 3, 5, 4);

	graph_insert_reb(p, 4, 1, 4);
	graph_insert_reb(p, 4, 2, 4);
	graph_insert_reb(p, 4, 3, 1);
	graph_insert_reb(p, 4, 4, 5);
	graph_insert_reb(p, 4, 5, 4);

	graph_insert_reb(p, 5, 1, 4);
	graph_insert_reb(p, 5, 2, 4);
	graph_insert_reb(p, 5, 3, 4);
	graph_insert_reb(p, 5, 4, 4);
	graph_insert_reb(p, 5, 5, 1);



	//cout << graph_get_reb(p, 4 ,2);






	//_getch(); 











	show_graph(p);




	
	int n = graph_size(p);
	//vector < vector<int> > g;
	const int INF = 1000000000; // значение "бесконечность"

								// алгоритм
	vector<bool> used(n); 
	vector<int> min_e(n, INF), sel_e(n, -1);
	min_e[0] = 0;

	for (int i = 0; i<n; ++i) 
	{
		int v = -1;

		//==========================================================================

		for (int j = 0; j<n; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;

		//==========================================================================



		if (min_e[v] == INF) {
			cout << "No MST!";
			exit(0);
		}

		//==========================================================================
		used[v] = true;

		//==========================================================================
		if (sel_e[v] != -1)
			cout << v+1 << " " << sel_e[v]+1 << endl;

		//==========================================================================
		for (int to = 0; to<n; ++to)
			if (graph_get_reb(p,v,to) < min_e[to]) 
			{
				min_e[to] = graph_get_reb(p, v, to);
				sel_e[to] = v;
			}

		//==========================================================================
	}

	_getch();
	
}

