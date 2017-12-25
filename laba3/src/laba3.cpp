#include <iostream>
#include <queue>
#include "orgraph.h"
#include <stack>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
	int vertexNumber, edgeNumber;
	cout << "Enter vertex number: ";
	cin >> vertexNumber;
	OrGraph *gr = create_orghraph(vertexNumber);
	for (int i = 0; i < vertexNumber; i++) {
		orgraph_set_vertex_label(gr, i, INT_MAX);
	}
	cout << "Enter edge number: ";
	cin >> edgeNumber;
	cout << "Enter edges:\n";
	for (int i = 0; i < edgeNumber; i++) {
		int a, b, w;
		cin >> a >> b >> w;
		orgraph_add_edge(gr, a, b);
		orgraph_add_edge(gr, b, a);
		orgraph_set_edge_weight(gr, a, b, w);
		orgraph_set_edge_weight(gr, b, a, w);
	}
	int from, to;
	cout << "Enter searching path: \n";
	cin >> from >> to;
	int cameFrom[vertexNumber];
	fill_n(cameFrom, 10, -1);
	queue<int> q;
	q.push(from);
	orgraph_set_vertex_label(gr, from, 0);
	int paths[vertexNumber];
	int pathsSize;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		pathsSize = 0;
		for (int i = 0; i < vertexNumber; i++) {
			if (orgraph_get_edge_weight(gr, current, i) != -1 &&
					orgraph_get_vertex_label(gr, i) >= 0) {
				paths[pathsSize] = i;
				pathsSize++;
			}
		}
		for (int i = 0; i < pathsSize - 1; i++) {
			for (int j = 0; j < pathsSize - i - 1; j++) {
				if (orgraph_get_edge_weight(gr, current, paths[j])
						> orgraph_get_edge_weight(gr, current, paths[j + 1])) {
					int temp = paths[j];
					paths[j] = paths[j + 1];
					paths[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < pathsSize; i++) {
			int newLabel = orgraph_get_vertex_label(gr, current)
					+ orgraph_get_edge_weight(gr, current, paths[i]);
			if (newLabel < orgraph_get_vertex_label(gr, paths[i])) {
				int oldLabel = orgraph_get_vertex_label(gr, paths[i]);
				orgraph_set_vertex_label(gr, paths[i], newLabel);
				cameFrom[paths[i]] = current;
				if (oldLabel == INT_MAX) {
					q.push(paths[i]);
				}
			}
		}
		orgraph_set_vertex_label(gr, current, ~orgraph_get_vertex_label(gr, current));
	}
	delete_orgraph(gr);
	stack<int> st;
	int i = to;
	while (i != -1) {
		st.push(i);
		i = cameFrom[i];
	}
	while (!st.empty()) {
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
	return 0;
}

/*
6
9
0 1 7
0 2 9
0 5 14
1 2 10
1 3 15
2 3 11
2 5 2
3 4 6
4 5 9
0 4
 */
