#include "Graf.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

int INF = 1e+9;
int NearestVertex(Graf *Graf, int vertex, bool visited[]);


int main() {
	int size = 1,
		*arr = new int[size],
		vertex = 0,
		min = INF,
		weight = 0,
		n, i, v, adv, w;
	
	cout << "Enter number of vertices : ";
	cin >> n;
	cout << "Enter number of edges : ";
	cin >> i;
	cout << "Enter the edges and their weight!" << endl;

	Graf *g = graf_create(n);
	Graf *tree = graf_create(n);
	bool *visited = new bool[n];
	memset(visited, false, n);

	for (i; i > 0; i--) {
		cin >> v >> adv >> w;
		graf_set_advertex(g, v, adv);
		graf_add_mark_edge(g, v, adv, w);
	}

/*	graf_set_advertex(g, 0, 1);
	graf_set_advertex(g, 0, 3);
	graf_set_advertex(g, 1, 3);
	graf_set_advertex(g, 1, 2);
	graf_set_advertex(g, 1, 4);
	graf_set_advertex(g, 2, 4);
	graf_set_advertex(g, 3, 4);
	graf_set_advertex(g, 3, 5);
	graf_set_advertex(g, 4, 5);
	graf_set_advertex(g, 4, 6);
	graf_set_advertex(g, 5, 6);

	graf_add_mark_edge(g, 0, 1, 7);
	graf_add_mark_edge(g, 0, 3, 5);
	graf_add_mark_edge(g, 1, 3, 9);
	graf_add_mark_edge(g, 1, 2, 8);
	graf_add_mark_edge(g, 1, 4, 7);
	graf_add_mark_edge(g, 2, 4, 5);
	graf_add_mark_edge(g, 3, 4, 15);
	graf_add_mark_edge(g, 3, 5, 6);
	graf_add_mark_edge(g, 4, 5, 8);
	graf_add_mark_edge(g, 4, 6, 9);
	graf_add_mark_edge(g, 5, 6, 11);  */

	arr[0] = vertex;
	while (true) {
		min = INF;
		if (size >= n) break;
		for (int i = 0; i < size; i++) {
			if (NearestVertex(g, arr[i], visited) < min) {
				min = NearestVertex(g, arr[i], visited);
				vertex = arr[i];
			}
		}
		if (min == INF) {
			cout << "The graph is not coherent!" << endl;
			system("pause");
			return 0;
		}
		arr[size] = min;
		size++;
		visited[min] = true;
		graf_set_advertex(tree, vertex, min);
		graf_add_mark_edge(tree, vertex, min, graf_get_mark_edge(g, vertex, min));
	}

	for (int i = 0; i < size; i++) {
		Iterator *it1 = iterator_begin(tree, i);
		Iterator *it2 = iterator_end(tree, i);
		cout << i;
		for (it1; !iterator_equal(it1, it2); iterator_next(it1)) {
			cout << " -> " << iterator_value(it1);
			weight += graf_get_mark_edge(tree, i, iterator_value(it1));
		}
		cout << endl;
	}
	cout << endl << "Weight of spanning tree : " << weight << endl << endl;
	system("pause");
	return 0;
}



int NearestVertex(Graf *Graf, int vertex, bool visited[]) {
	int min = INF, minV = INF;
	Iterator *it1 = iterator_begin(Graf, vertex);
	Iterator *it2 = iterator_end(Graf, vertex);
	for (it1; !iterator_equal(it1, it2); iterator_next(it1)) {
		if (graf_get_mark_edge(Graf, vertex, iterator_value(it1)) < min) {
			if (visited[iterator_value(it1)] == false) {
				min = graf_get_mark_edge(Graf, vertex, iterator_value(it1));
				minV = iterator_value(it1);
			}
		}
	}
	return minV;
}