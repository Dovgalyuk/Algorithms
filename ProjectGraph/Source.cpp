#include "../Library/orGraph.h"
#include <iostream>
#include <vector>
using namespace std;

int main() 
{
	Graph *p;

	p = graph_create(5);

	
	int n;
	vector < vector<int> > g;
	const int INF = 1000000000; // значение "бесконечность"

								// алгоритм
	vector<bool> used(n);
	vector<int> min_e(n, INF), sel_e(n, -1);
	min_e[0] = 0;

	for (int i = 0; i<n; ++i) 
	{
		int v = -1;
		for (int j = 0; j<n; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;
		if (min_e[v] == INF) {
			cout << "No MST!";
			exit(0);
		}

		used[v] = true;
		if (sel_e[v] != -1)
			cout << v << " " << sel_e[v] << endl;

		for (int to = 0; to<n; ++to)
			if (g[v][to] < min_e[to]) {
				min_e[to] = g[v][to];
				sel_e[to] = v;
			}
	}
	
}

