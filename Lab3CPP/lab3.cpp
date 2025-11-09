#include <iostream>
#include<fstream>
#include <map>
#include <algorithm>
#include <vector>
#include "queue.h"

using namespace std;

typedef map<size_t, vector<size_t>> Graph;

void add_rebra_int_Graph(Graph& graph, size_t& a, size_t& b) {
	graph[a].push_back(b);
	graph[b].push_back(a);
}


vector<size_t> bfs(Graph& graph, size_t& start, size_t& end) {
	map<size_t, bool> visited;
	map<size_t, size_t> parent;
	Queue* queue = queue_create();

	queue_insert(queue, start);
	visited[start] = true;

	while (!queue_empty(queue)) {

		size_t tecuchie = queue_get(queue);
		queue_remove(queue);

		if (tecuchie == end) {
			break;
		}

		for (size_t& v : graph[tecuchie]) {

			if (!visited[v]) {

				visited[v] = true;
				parent[v] = tecuchie;
				queue_insert(queue, v);
			}
		}
	}
	queue_delete(queue);

	vector<size_t> path;
	if (!visited[end]) {
		return path;
	}

	for (size_t v = end; v != start; v = parent[v])
		path.push_back(v);
	path.push_back(start);

	reverse(path.begin(), path.end());
	return path;
}

int main(int argc, char** argv) {
	(void)argc;

	ifstream file1(argv[1]);
	ofstream file2("output.txt");

	if (!file1.is_open()) {
		return 1;
	}
	if (!file2.is_open()){
		return 1;
	}

	Graph graph;
	size_t a, b;
	while (file1 >> a >> b) {
		add_rebra_int_Graph(graph, a, b);
	}

	size_t start, end;
	if (!(file1 >> start >> end)) {
		return 1;
	}
	vector<size_t> path = bfs(graph, start, end);


	if (path.empty()) {
		file2 << "No path";
	}
	else {
		for (size_t i = 0; i < path.size(); ++i) {

			file2 << path[i];
			if (i + 1 < path.size()){

				file2 << " ";
			}
		}
	}

	file1.close();
	file2.close();
	return 0;
}