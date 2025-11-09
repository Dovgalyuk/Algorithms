#include <iostream>
#include<fstream>
#include <map>
#include <algorithm>
#include "queue.h"
#include "vector.h"	

using namespace std;

typedef map<string, Vector*> Graph;
typedef map<string, string> Roditel;
typedef map<string, bool> Visited;

void add_rebra_int_Graph(Graph& graph, string& a,string& b) {
	if (!graph[a]) {
		graph[a] = vector_create();
	}
	if (!graph[b]) {
		graph[b] = vector_create();
	}

	vector_push_back(graph[a], b);
	vector_push_back(graph[b], a);
}


vector<string> bfs(Graph& graph, string& start, string& end) {
	Visited visited;
	Roditel roditel;
	Queue* queue = queue_create();

	queue_insert(queue, start);
	visited[start] = true;

	while (!queue_empty(queue)) {

		string tecuchie = queue_get(queue);
		queue_remove(queue);

		if (tecuchie == end) {
			break;
		}

		for (size_t i = 0; i < vector_size(graph[tecuchie]); i++) {

			string sledueshee = vector_get(graph[tecuchie], i);

			if (!visited[sledueshee]) {
				visited[sledueshee] = true;
				roditel[sledueshee] = tecuchie;

				queue_insert(queue, sledueshee);
			}
		}
	}
	queue_delete(queue);

	vector<string> path;
	if (!visited[end]) {
		return path;
	}

	for (string v = end; !v.empty(); v = roditel.count(v) ? roditel[v] : "") {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}

int main(int argc, char** argv) {
	(void)argc;

	ifstream file1(argv[1]);
	ofstream fout("output.txt");

	if (!file1.is_open()) {
		return 1;
	}
	if (!fout.is_open()){
		return 1;
	}

	Graph graph;
	string a, b;
	while (file1 >> a >> b) {
		add_rebra_int_Graph(graph, a, b);
	}

	string start, end;
	if (!file1 >> start >> end) {
		return 1;
	}
	vector<string> path = bfs(graph, start, end);


	if (path.empty()) {
		fout << "No path";
	}
	else {
		for (size_t i = 0; i < path.size(); ++i) {
			fout << path[i];
			if (i + 1 < path.size()) fout << " ";
		}
	}

	fout.close();

	for (auto& a : graph) {
		vector_delete(a.second);
	}
	return 0;
}